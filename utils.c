/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:59:41 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/21 21:17:42 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(char *str)
{
	int			count;
	long		number;

	count = 0;
	number = 0;
	while (*str == '0' || *str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (ft_write("A number Can't be negative", 2), -1);
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (ft_write("Please Provide a valid number", 2), -1);
		number = number * 10 + (*str++ - 48);
		count++;
	}
	if (count >= 20 || number > LONG_MAX)
		return (ft_write("Please Provide a valid number", 2), -1);
	printf("number : %ld\n", number);
	return (number);
}
