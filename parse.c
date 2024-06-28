/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:44:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/28 23:09:09 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(t_table *tabla)
{
	if (tabla->number_of_philo == -1 || tabla->time_to_die == -1 \
	|| tabla->time_to_eat == -1 || tabla->time_to_sleep == -1)
		return (0);
	if (!tabla->number_of_philo || !tabla->time_to_die
		|| !tabla->time_to_eat || !tabla->time_to_sleep || \
		!tabla->number_of_meals)
		return (ft_write("Invalid arg", 2), 0);
	return (1);
}

int	parse_input(t_table *tabla, int ac, char **av)
{
	int	ret;

	tabla->number_of_philo = ft_atoi(av[1]);
	tabla->time_to_die = ft_atoi(av[2]);
	tabla->time_to_eat = ft_atoi(av[3]);
	tabla->time_to_sleep = ft_atoi(av[4]);
	tabla->death = 0;
	if (ac == 6)
	{
		tabla->number_of_meals = ft_atoi(av[5]);
		if (tabla->number_of_meals == -1)
			return (2);
	}
	else
		tabla->number_of_meals = -1;
	if (!check_number(tabla))
		return (2);
	if (pthread_mutex_init(&tabla->print, NULL) == -1)
		return (ft_write("Mutex init failed", 2), 2);
	if (pthread_mutex_init(&tabla->death_mut, NULL) == -1)
		return (ft_write("Mutex init failed", 2), 2);
	ret = init_var(tabla);
	return (ret);
}

void	set_forks(t_table *tabla)
{
	int	i;

	tabla->philos[0].l_fork = &tabla->forks[0];
	tabla->philos[0].r_fork = &tabla->forks[tabla->number_of_philo - 1];
	i = 1;
	while (i < tabla->number_of_philo)
	{
		tabla->philos[i].l_fork = &tabla->forks[i];
		tabla->philos[i].r_fork = &tabla->forks[i - 1];
		i++;
	}
}

int	init_var(t_table *tabla)
{
	int	i;

	i = -1;
	tabla->philos = malloc(sizeof(t_philo) * tabla->number_of_philo);
	if (!tabla->philos)
		return (ft_write("Malloc failed", 2), 4);
	tabla->forks = malloc(sizeof(pthread_mutex_t) * tabla->number_of_philo);
	if (!tabla->forks)
		return (free(tabla->philos), ft_write("Malloc failed", 2), 4);
	while (++i < tabla->number_of_philo)
	{
		tabla->philos[i].is_dead = 0;
		tabla->philos[i].id = i + 1;
		tabla->philos[i].tabla = tabla;
		tabla->philos[i].last_meal = get_time();
		tabla->philos[i].meal_c = 0;
		if (pthread_mutex_init(&tabla->forks[i], NULL) == -1)
			return (ft_write("Mutex init failed", 2), 2);
		if (pthread_mutex_init(&tabla->philos[i].last_meal_mutex, NULL) == -1)
			return (ft_write("Mutex init failed", 2), 2);
		if (pthread_mutex_init(&tabla->philos[i].meal_counter_mut, NULL) == -1)
			return (ft_write("Mutex init failed", 2), 2);
	}
	set_forks(tabla);
	return (1);
}
