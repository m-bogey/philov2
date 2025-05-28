/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:17:42 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/27 19:19:25 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TESTINTMAX "2147483647"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_my_mutex
{
	pthread_mutex_t	m;
	int				m_init;
}				t_my_mutex;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			can_use;
	int				init;
}				t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	t_table		*table;
	pthread_t	id_thread;
	int			id;
	long		count_meals;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_my_mutex	mutex_full;
	bool		full;
	t_my_mutex	mutex_time_last_meal;
	long		time_last_meal;
}				t_philo;

typedef struct s_table
{
	pthread_t		check_philos;
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals;
	t_fork			*forks;
	t_philo			*philos;

	t_my_mutex		mutex_ready;
	bool			philos_ready;
	t_my_mutex		mutex_end;
	bool			end_simulation;
	t_my_mutex		mutex_start_time;
	long			start_time;
	t_my_mutex		mutex_can_write;
	bool			can_write;
}				t_table;

int		parsing(int argc, char **argv);
int		init(t_table *table, int argc, char **argv);
void	start_simulation(t_table *table);
long	getime(t_table *table);
void	*routine(void *arg);
void	usleep_with_check_die(long usec, t_table *table);
void	print_mutex(t_philo *philo, char *str);
void	print_mutex_end(t_philo *philo, char *str);
void	*check_end_simulation(void *arg);

bool	wait_for_begin(t_table *table);
void	clean(t_table *table);

int		safe_init_mutex(t_my_mutex *my_mutex);
int		safe_init_fork(t_fork *f);

long	ft_atol(char *str);

#endif
