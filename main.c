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
	// if (philo->tabla->print_c)
	// 	return ;
	printf("%llu %d %s\n", get_time() - philo->tabla->start, philo->id, str);
	pthread_mutex_unlock(&philo->tabla->print);
}

void *monitor(void *p)
{
    t_table *tabla;
    tabla = (t_table *)p;
	int x;
	int count = 0;

    while (1)
    {
		x = 0;
		while (x < tabla->number_of_philosophers)
		{
			if (tabla->number_of_meals != -1)
			{
				if (tabla->philos[x].meal_c == tabla->number_of_meals)
				{
					count++;
				}
				if (count == tabla->number_of_meals)
					return (NULL);
			}
			if (get_time() - tabla->philos[x].last_meal >= tabla->time_to_die)
			{
				pthread_mutex_lock(&tabla->print);
				printf("%llu %d died\n", get_time() - tabla->start, tabla->philos[x].id);
				return (NULL);
			}
			x++;
		}
    }
    return NULL;
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
        philo->last_meal = get_time();
		philo->meal_c += 1;
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
	pthread_mutex_init(&tabla.death_mut, NULL);
	for (int i = 0; i < tabla.number_of_philosophers; i++) {
		if (pthread_create(&tabla.philos[i].th, NULL, &routine, &tabla.philos[i]) == -1)
			perror("create");
		pthread_detach(tabla.philos[i].th);
	}
	if (pthread_create(&monitor_th, NULL, &monitor, &tabla) == -1)
			perror("create");
	if  (pthread_join(monitor_th, NULL) == -1)
			perror("join");
	// printf("sleeping for 30 sec\n");
	// ft_usleep(30000);
	// printf("DONE\n");
}
