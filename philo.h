/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:09:32 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/29 00:11:35 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				meal_c;
	long			last_meal;
	pthread_t		th;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_table			*tabla;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meal_counter_mut;
}				t_philo;

typedef struct s_table
{
	int				number_of_philo;
	long			start;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	int				number_of_meals;
	int				death;
	t_philo			*philos;
	pthread_mutex_t	death_mut;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_table;

// utils
long		ft_atoi(char *str);
void		ft_write(char *str, int fd);
int			parse_input(t_table *tabla, int ac, char **av);
long		get_time(void);
void		ft_usleep(long time);
int			init_var(t_table *tabla);
void		*routine(void *p);
void		*monitor(void *p);
void		print_status(t_philo *philo, char *str);

#endif