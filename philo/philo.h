/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:23:27 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/01 11:34:33 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

// Structs

typedef struct	table
{
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	n_meals;
}				t_table;

// Functions
void	ft_write(char *str, int fd);
void	parsing(int nb, char **args, t_table *table);
char	**ft_split(char const *s, char c);

#endif