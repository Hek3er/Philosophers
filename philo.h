#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	pthread_t		th;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_table			*tabla;
}				t_philo;

typedef struct s_table
{
	int				number_of_philosophers;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	uint64_t		number_of_meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}				t_table;

// utils
uint64_t	ft_atoi(char *str);
void		throw_error(char *str, int code);
void		parse_input(t_table *tabla, int ac, char **av);
void		ft_usleep(useconds_t utime);

#endif