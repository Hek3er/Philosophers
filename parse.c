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
	if (!tabla->number_of_philosophers)
		throw_error("Number of philo can't be 0", 2);
}

void	init_var(t_table *tabla)
{
	int	i;

	i = 0;
	tabla->philos = malloc(sizeof(t_philo) * tabla->number_of_philosophers);
	if (!tabla->philos)
		throw_error("Malloc Failed", 3);
	while (i < tabla->number_of_philosophers)
	{
		tabla->philos[i].is_dead = 0;
		tabla->philos[i].id = i + 1;
		tabla->philos[i].tabla = tabla;
		i++;
	}
}
