/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:35:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/20 18:14:40 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *str)
{
	// // int death ;
	// pthread_mutex_lock(&philo->tabla->death_mut);
	// 	// printf("%d\n", philo->tabla->death);
	// if (philo->tabla->death)
	// {
	// 	usleep(500);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->tabla->death_mut);
	pthread_mutex_lock(&philo->tabla->print);
	printf("%ld %d %s\n", get_time() - philo->tabla->start, philo->id, str);
	pthread_mutex_unlock(&philo->tabla->print);
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	start_sim(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
	}
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	philo->meal_c += 1;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo->tabla->time_to_eat);
	unlock_forks(philo);
	print_msg(philo, "is sleeping");
	ft_usleep(philo->tabla->time_to_sleep);
	print_msg(philo, "is thinking");
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
		{
			pthread_mutex_unlock(&philo->tabla->death_mut);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->tabla->death_mut);
		start_sim(philo);
	}
	return (NULL);
}
