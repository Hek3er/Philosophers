/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:24:00 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/22 13:29:27 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) == -1)
		throw_error("Gettimeofdat Failed", 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(uint64_t	time)
{
	uint64_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(500);
}