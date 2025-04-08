#ifndef PHILO_H
# define PHILO_H

# define TESTINTMAX "2147483647"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			can_use;
	int				init;
}				t_fork;

typedef struct s_table t_table;

typedef struct s_philo
{
	t_table		*table;
	pthread_t	id_thread;
	int			id;
	long		count_meals;
	bool		full;
	long		time_last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
}				t_philo;


typedef struct s_table
{
	pthread_t		check_philos;
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals;
	long			start_time;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	mutex_print;
	int				mutex_print_init;
	bool			end_simulation;
	bool			can_write;
	bool			philos_ready;
	pthread_mutex_t	mutex_ready;
	int				mutex_ready_init;
}				t_table;

int		parsing(int argc, char **argv);
void	init(t_table *table, int argc, char **argv);
void	start_simulation(t_table *table);
long	getime(t_table *table);
void	*routine(void *arg);
void	usleep_with_check_die(long usec, t_table *table);
void	print_mutex(t_philo *philo, char *str);
void	*check_end_simulation(void *arg);

bool	wait_for_begin(t_table *table);
void	clean(t_table *table);
void	exit_clean(t_table *table);

#endif