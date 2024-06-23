/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:28:31 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/23 10:58:54 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *p)
{
    t_philo *philo;
	uint64_t	last_meal;
	int			meal_c = 0;
    philo = (t_philo *)p;
    while (1)
    {
		pthread_mutex_lock(&philo->tabla->last_meal_mutex);
		if (philo->meal_c == philo->tabla->number_of_meals) {
			pthread_mutex_unlock(&philo->tabla->last_meal_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->tabla->last_meal_mutex);
		pthread_mutex_lock(&philo->tabla->last_meal_mutex);
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->tabla->last_meal_mutex);
        pthread_mutex_lock(&philo->tabla->death_mutex);
        if (!meal_c && last_meal && get_time() - last_meal > philo->tabla->time_to_die) {
            printf("%llu %d died\n", get_time() - philo->tabla->start, philo->id);
            philo->tabla->death = 1;
            pthread_mutex_unlock(&philo->tabla->death_mutex);
            exit(2);
			// return (NULL);
        }
        pthread_mutex_unlock(&philo->tabla->death_mutex);
    }
    return NULL;
}

void	print_status(t_philo *philo, char *str)
{
	printf("%llu %d %s\n", get_time() - philo->tabla->start, philo->id, str);
}

void	unlock_mutex_philo(t_philo *philo)
{
	if (philo->id %2 == 0) {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
	} else {
		pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
	}
}

void *routine(void *p)
{
    t_philo *philo;
    philo = (t_philo *)p;
    while (1)
    {
		if (philo->id % 2 == 0) {
        	pthread_mutex_lock(philo->l_fork);
        	print_status(philo, "has taken a fork");
        	pthread_mutex_lock(philo->r_fork);
       		print_status(philo, "has taken a fork");
		}
		else {
			pthread_mutex_lock(philo->r_fork);
        	print_status(philo, "has taken a fork");
        	pthread_mutex_lock(philo->l_fork);
       		print_status(philo, "has taken a fork");
		}
		
        print_status(philo, "is eating");
		pthread_mutex_lock(&philo->tabla->meal_counter_mutex);
		philo->meal_c += 1;
		if (philo->meal_c == philo->tabla->number_of_meals) {
			pthread_mutex_unlock(&philo->tabla->meal_counter_mutex);
			unlock_mutex_philo(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->tabla->meal_counter_mutex);
		pthread_mutex_lock(&philo->tabla->last_meal_mutex);
        philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->tabla->last_meal_mutex);
        ft_usleep(philo->tabla->time_to_eat);

		unlock_mutex_philo(philo);

        print_status(philo, "is sleeping");
        ft_usleep(philo->tabla->time_to_sleep);

        print_status(philo, "is thinking");
    }
    return NULL;
}

int	main(int ac, char **av)
{
	t_table	tabla;

	if (ac == 5 || ac == 6)
	{
		parse_input(&tabla, ac, av);
	}
	else
	{
		throw_error("Invalid Arguments\n\
		Usage: ./philo [n_philos] [t_die] [t_eat] [t_sleep] {n_meal}(optional)", 1);
	}
	tabla.start = get_time();
	pthread_mutex_init(&tabla.death_mutex, NULL);
	pthread_mutex_init(&tabla.meal_counter_mutex, NULL);
	pthread_mutex_init(&tabla.last_meal_mutex, NULL);
	for (int i = 0; i < tabla.number_of_philosophers; i++) {
		if (pthread_create(&tabla.philos[i].th, NULL, &routine, &tabla.philos[i]) == -1)
			perror("create");
		pthread_detach(tabla.philos[i].th);
	}
	for (int i = 0; i < tabla.number_of_philosophers; i++) {
		if (pthread_create(&tabla.philos[i].th, NULL, &monitor, &tabla.philos[i]) == -1)
			perror("create");
	}
	for (int i = 0; i < tabla.number_of_philosophers; i++) {
		if  (pthread_join(tabla.philos[i].th, NULL) == -1)
			perror("join");
	}
	// printf("sleeping for 30 sec\n");
	// ft_usleep(30000);
	// printf("DONE\n");
}
