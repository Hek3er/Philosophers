/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:28:31 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/22 19:23:00 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->is_dead)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			printf("Philo %d has taken left fork at %llu\n", philo->id, get_time());
			pthread_mutex_lock(philo->r_fork);
			printf("Philo %d has taken right fork at %llu\n", philo->id, get_time());
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			pthread_mutex_lock(philo->l_fork);	
		}
		printf("Philo %d is eating at %llu\n", philo->id, get_time());
		ft_usleep(philo->tabla->time_to_sleep);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);	
		}
	}
	if (philo->is_dead)
		throw_error("exit", 20);
	return (0);
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

	for (int i = 0; i < tabla.number_of_philosophers; i++) {
		if (pthread_create(&tabla.philos[i].th, NULL, &routine, &tabla.philos[i]) == -1)
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
