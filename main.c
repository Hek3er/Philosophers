/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:28:31 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/28 23:09:09 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *tabla)
{
	int			i;
	pthread_t	monitor_th;

	i = 0;
	while (i < tabla->number_of_philo)
	{
		if (pthread_create(&tabla->philos[i].th, NULL, &routine, \
		&tabla->philos[i]) == -1)
			return (ft_write("pthread_destroy_failed\n", 2), 0);
		if (pthread_detach(tabla->philos[i].th) == -1)
			return (ft_write("pthread_destroy failed\n", 2), 0);
		i++;
	}
	if (pthread_create(&monitor_th, NULL, &monitor, tabla) == -1)
		return (ft_write("pthread_destroy failed\n", 2), 0);
	if (pthread_join(monitor_th, NULL) == -1)
		return (ft_write("pthread_destroy failed\n", 2), 0);
	return (1);
}

int	destroy(t_table *tabla)
{
	int	i;

	i = 0;
	while (i < tabla->number_of_philo)
	{
		if (pthread_mutex_destroy(&tabla->forks[i]) == -1)
			return (ft_write("pthread_destroy failed\n", 2), 0);
		if (pthread_mutex_destroy(&tabla->philos[i].last_meal_mutex) == -1)
			return (ft_write("pthread_destroy failed\n", 2), 0);
		if (pthread_mutex_destroy(&tabla->philos[i].meal_counter_mut) == -1)
			return (ft_write("pthread_destroy failed\n", 2), 0);
		i++;
	}
	if (pthread_mutex_destroy(&tabla->death_mut) == -1)
		return (ft_write("pthread_destroy failed\n", 2), 0);
	if (pthread_mutex_destroy(&tabla->print) == -1)
		return (ft_write("pthread_destroy failed\n", 2), 0);
	if (tabla->forks)
		free(tabla->forks);
	if (tabla->philos)
		free(tabla->philos);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	tabla;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&tabla, ac, av) != 1)
			return (1);
	}
	else
	{
		return (ft_write("Invalid Arguments\n\
		Usage: ./philo [n_philos] [t_die] [t_eat] [t_sleep] {n_meal}", 1), 1);
	}
	tabla.start = get_time();
	if (create_threads(&tabla) == 0)
	{
		destroy(&tabla);
		return (1);
	}
	if (destroy(&tabla) == 0)
		return (1);
}
