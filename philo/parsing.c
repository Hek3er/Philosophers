/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:23:07 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/01 11:37:34 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**join2d_arrays(char **args, char *tmp_arg)
{
	if (!args)
		return (NULL);
	
}

void	parsing(int nb, char **args, t_table *table)
{
	int		i;
	char	**tmp_args;

	i = 0;
	if (nb == 5)
	{
		while (i < nb)
		{
			tmp_args = ft_split(args[i], ' ');
			
			i++;
		}
	}
}