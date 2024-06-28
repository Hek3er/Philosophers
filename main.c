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

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->tabla->print);
	printf("%llu %d %s\n", get_time() - philo->tabla->start, philo->id, str);
	pthread_mutex_unlock(&philo->tabla->print);
}

int check_number_of_meals(t_table *tabla)
{
	int count = 0;
	int	meal_count = 0;
	int i = 0;

	while (i < tabla->number_of_philosophers)
	{
		pthread_mutex_lock(&tabla->philos[i].meal_counter_mutex);
		meal_count = tabla->philos[i].meal_c;
		pthread_mutex_unlock(&tabla->philos[i].meal_counter_mutex);
		if (meal_count >= tabla->number_of_meals)
			count++;
		i++;
	}
	if (count == tabla->number_of_philosophers)
		return (1);
	return (0);
}

int	check_philo_death(t_table *tabla)
{
	int			i;
	uint64_t	last_meal;

	i = 0;
	while (i < tabla->number_of_philosophers)
	{
		pthread_mutex_lock(&tabla->philos[i].last_meal_mutex);
		last_meal = tabla->philos[i].last_meal;
		pthread_mutex_unlock(&tabla->philos[i].last_meal_mutex);
		if (get_time() - last_meal > tabla->time_to_die)
		{
			pthread_mutex_lock(&tabla->print);
			printf("%llu %d died\n", get_time() - tabla->start, tabla->philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

void *monitor(void *p)
{
    t_table *tabla;
    tabla = (t_table *)p;

    while (1)
    {
		if (tabla->number_of_meals != -1)
		{
			if (check_number_of_meals(tabla))
				return (NULL);
		}
		if (check_philo_death(tabla))
			return (NULL);
		usleep(100);
	}
    return NULL;
}


void	unlock_mutex_philo(t_philo *philo)
{
	if (philo->id % 2 == 0) {
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

	if (philo->id % 2 == 0)
		usleep(50);

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

		pthread_mutex_lock(&philo->last_meal_mutex);
        philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		
		pthread_mutex_lock(&philo->meal_counter_mutex);
		philo->meal_c++;
		pthread_mutex_unlock(&philo->meal_counter_mutex);


        ft_usleep(philo->tabla->time_to_eat);
		unlock_mutex_philo(philo);
		// pthread_mutex_unlock(philo->l_fork);
        // pthread_mutex_unlock(philo->r_fork);
        print_status(philo, "is sleeping");
        ft_usleep(philo->tabla->time_to_sleep);
        print_status(philo, "is thinking");
    }
    return NULL;
}

int	main(int ac, char **av)
{
	t_table	tabla;
	pthread_t	monitor_th;

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
	pthread_mutex_init(&tabla.print, NULL);
	// pthread_mutex_init(&tabla.lastmeal_mut, NULL);
	for (int i = 0; i < tabla.number_of_philosophers; i++) {
		if (pthread_create(&tabla.philos[i].th, NULL, &routine, &tabla.philos[i]) == -1)
			perror("create");
		pthread_detach(tabla.philos[i].th);
	}
	if (pthread_create(&monitor_th, NULL, &monitor, &tabla) == -1)
			perror("create");
	if  (pthread_join(monitor_th, NULL) == -1)
			perror("join");
}
