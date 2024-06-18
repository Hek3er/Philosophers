/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:44:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/24 15:52:25 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 /* FT_ATOI */
void	parse_input(t_table *tabla, int ac, char **av)
{
	tabla->number_of_philosophers = ft_atoi(av[1]);
	tabla->time_to_die = ft_atoi(av[2]);
	tabla->time_to_eat = ft_atoi(av[3]);
	tabla->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		tabla->number_of_meals = ft_atoi(av[5]);
	else
		tabla->number_of_meals = -1;
	if (!tabla->number_of_philosophers || !tabla->time_to_die 
	|| !tabla->time_to_eat || !tabla->time_to_sleep)
		throw_error("Invalid Arguments", 2);
}

void	init_var(t_table *tabla)
{
	int	i;

	i = 0;
	tabla->philos = malloc(sizeof(t_philo) * tabla->number_of_philosophers);
	if (!tabla->philos)
		throw_error("Malloc Failed", 3);
	tabla->forks = malloc(sizeof(pthread_mutex_t) * tabla->number_of_philosophers);
	if (!tabla->forks)
		throw_error("Malloc Failed", 3);
	while (i < tabla->number_of_philosophers)
	{
		tabla->philos[i].is_dead = 0;
		tabla->philos[i].id = i + 1;
		tabla->philos[i].tabla = tabla;
		pthread_mutex_init(&tabla->forks[i], NULL);
		i++;
	}
	tabla->philos[0].l_fork = &tabla->forks[0];
	tabla->philos[0].r_fork = &tabla->forks[tabla->number_of_philosophers - 1];
	i = 1;
	while (i < tabla->number_of_philosophers)
	{
		tabla->philos[i].l_fork = &tabla->forks[i];
		tabla->philos[i].r_fork = &tabla->forks[i - 1];
	}
}
