/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:35:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/28 23:11:16 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->tabla->death_mut);
	if (!philo->tabla->death)
	{
		pthread_mutex_lock(&philo->tabla->print);
		printf("%ld %d %s\n", get_time() - philo->tabla->start, philo->id, str);
		pthread_mutex_unlock(&philo->tabla->print);
	}
	pthread_mutex_unlock(&philo->tabla->death_mut);
}

void	unlock_mutex_philo(t_philo *philo)
{
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

void	pick_forks_and_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_counter_mut);
	philo->meal_c++;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->meal_counter_mut);
	ft_usleep(philo->tabla->time_to_eat);
	unlock_mutex_philo(philo);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&philo->tabla->death_mut);
		if (philo->tabla->death)
			break ;
		pthread_mutex_unlock(&philo->tabla->death_mut);
		pick_forks_and_eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->tabla->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
