/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:24:00 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/29 00:13:21 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_write("gettimeofday failed", 2), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = get_time();
	if (start_time == -1)
		return ;
	while (get_time() - start_time < time)
		usleep(500);
}
