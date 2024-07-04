/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:59:41 by azainabi          #+#    #+#             */
/*   Updated: 2024/07/04 03:32:33 by azainabi         ###   ########.fr       */
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

int	ft_isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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
	int							i;
	int							neg;
	unsigned long long			ret;

	i = 0;
	neg = 1;
	ret = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (ft_write("A number Can't be negative", 2), -1);
		i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isnumber(str[i]))
			return (ft_write("Please Provide a valid number", 2), -1);
		ret = ret * 10 + (str[i++] - '0');
	}
	if (ret > LONG_MAX)
		return (ft_write("Please Provide a valid number", 2), -1);
	return (ret * neg);
}
