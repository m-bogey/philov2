#ifndef table_H
# define table_H

# define TESTINTMAX "2147483647"

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			is_available;
}				t_fork;

typedef struct s_philo
{
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
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_meals;
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

int		parsing(int argc, char **argv);
void	init(t_table *table, int argc, char **argv);
void	start_simulation(t_table *table);
#endif