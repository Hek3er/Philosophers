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
	int				meal_c;
	uint64_t		last_meal;
	pthread_t		th;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_table			*tabla;
	pthread_mutex_t	last_meal_mutex;
	// pthread_mutex_t	print;
	pthread_mutex_t	meal_counter_mutex;
}				t_philo;

typedef struct s_table
{
	int				number_of_philosophers;
	uint64_t		start;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	int				number_of_meals;
	int				print_c;
	int				death;
	// int				fixed_meals;
	t_philo			*philos;
	pthread_mutex_t	death_mut;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_table;

// utils
uint64_t	ft_atoi(char *str);
void		ft_write(char *str, int fd);
void		throw_error(char *str, int code);
void		parse_input(t_table *tabla, int ac, char **av);
uint64_t	get_time(void);
void		ft_usleep(uint64_t	time);
void		init_var(t_table *tabla);

#endif