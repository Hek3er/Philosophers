/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:12:43 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/20 18:12:20 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number_of_meals(t_table *tabla)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (++i < tabla->number_of_philo)
	{
		pthread_mutex_lock(&tabla->philos[i].last_meal_mutex);
		if (tabla->philos[i].meal_c >= tabla->number_of_meals)
			count++;
		pthread_mutex_unlock(&tabla->philos[i].last_meal_mutex);
		if (count == tabla->number_of_philo)
			return (1);
	}
	return (0);
}

int	check_philo_death(t_table *tabla)
{
	int		i;
	long	last_meal;

	i = -1;
	while (++i < tabla->number_of_philo)
	{
		pthread_mutex_lock(&tabla->philos[i].last_meal_mutex);
		last_meal = tabla->philos[i].last_meal;
		pthread_mutex_unlock(&tabla->philos[i].last_meal_mutex);
		// printf("last_meal %ld\n", get_time() - last_meal);
		if (get_time() - last_meal > tabla->time_to_die)
		{
			// print_msg(&tabla->philos[i], "has died");
			pthread_mutex_lock(&tabla->death_mut);
			tabla->death = 1;
			pthread_mutex_unlock(&tabla->death_mut);
			pthread_mutex_lock(&tabla->print);
			printf("%ld %d died\n", get_time() - tabla->start, tabla->philos[i].id);
			// pthread_mutex_unlock(&tabla->print);
			return (1);
		}
		// usleep(500);
	}
	return (0);
}

void	*monitor(void *p)
{
	t_table	*tabla;

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
	}
	return (NULL);
}
