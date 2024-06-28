/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:12:43 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/28 23:09:09 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number_of_meals(t_table *tabla)
{
	int	count;
	int	meal_count;
	int	i;

	count = 0;
	meal_count = 0;
	i = 0;
	while (i < tabla->number_of_philo)
	{
		pthread_mutex_lock(&tabla->philos[i].meal_counter_mut);
		meal_count = tabla->philos[i].meal_c;
		pthread_mutex_unlock(&tabla->philos[i].meal_counter_mut);
		if (meal_count >= tabla->number_of_meals)
			count++;
		i++;
	}
	if (count == tabla->number_of_philo)
		return (1);
	return (0);
}

int	check_philo_death(t_table *tabla)
{
	int			i;
	long		last_meal;

	i = 0;
	while (i < tabla->number_of_philo)
	{
		pthread_mutex_lock(&tabla->philos[i].last_meal_mutex);
		last_meal = tabla->philos[i].last_meal;
		pthread_mutex_unlock(&tabla->philos[i].last_meal_mutex);
		if (get_time() - last_meal > tabla->time_to_die)
		{
			pthread_mutex_lock(&tabla->death_mut);
			tabla->death = 1;
			pthread_mutex_lock(&tabla->print);
			printf("%ld %d died\n", get_time() - tabla->start, \
			tabla->philos[i].id);
			pthread_mutex_unlock(&tabla->print);
			pthread_mutex_unlock(&tabla->death_mut);
			return (1);
		}
		i++;
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
