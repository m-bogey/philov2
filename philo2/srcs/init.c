#include "philo.h"

static long		ft_atol(char *str);
static void		init_mutex(t_table *table);
static void		init_philo(t_table *table);
static void		what_fork(t_philo *philo, t_fork *forks, long i, int nb_philo);

void	init(t_table *table, int argc, char **argv)
{
	table->nb_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argc == 6)
		table->nb_meals = ft_atol(argv[5]);
	else
		table->nb_meals = -1;
	table->end_simulation = false;
	table->can_write = true;

	table->start_time = -1;
	table->philos_ready = false;
	table->philos = NULL;
	table->forks = NULL;
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		exit_clean(table);
	table->forks = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->forks)
		exit_clean(table);
	init_mutex(table);
	init_philo(table);
}

static long		ft_atol(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

static void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->forks[i].init = 0;
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			exit_clean(table);
		table->forks[i].can_use = true;
		table->forks[i].init = 1;
		i++;
	}
	table->mutex_print_init = 0;
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		exit_clean(table);
	table->mutex_print_init = 1;
	table->mutex_ready_init = 0;
	if (pthread_mutex_init(&table->mutex_ready, NULL) != 0)
		exit_clean(table);
	table->mutex_ready_init = 1;
	table->mutex_end_init = 0;
	if (pthread_mutex_init(&table->mutex_end, NULL) != 0)
		exit_clean(table);
	table->mutex_end_init = 1;
	table->mutex_meal_init = 0;
	if (pthread_mutex_init(&table->mutex_meal, NULL) != 0)
		exit_clean(table);
	table->mutex_meal_init = 1;
	table->mutex_full_init = 0;
	if (pthread_mutex_init(&table->mutex_full, NULL) != 0)
		exit_clean(table);
	table->mutex_full_init = 1;
	table->mutex_time_init = 0;
	if (pthread_mutex_init(&table->mutex_time, NULL) != 0)
		exit_clean(table);
	table->mutex_time_init = 1;
	table->mutex_end_sim_init = 0;
	if (pthread_mutex_init(&table->mutex_end_sim, NULL) != 0)
		exit_clean(table);
	table->mutex_end_sim_init = 1;
	table->mutex_canwrite_init = 0;
	if (pthread_mutex_init(&table->mutex_canwrite, NULL) != 0)
		exit_clean(table);
	table->mutex_canwrite_init = 1;
}

static void		init_philo(t_table *table)
{
	t_philo	*philo;
	long	j;

	j = 0;
	while (j < table->nb_philo)
	{
		philo = table->philos + j;
		philo->table = table;
		philo->id = j + 1;
		philo->count_meals = 0;
		philo->full = false;
		philo->time_last_meal = 0;
		what_fork(philo, table->forks, j, table->nb_philo);
		j++;
	}
}
static void		what_fork(t_philo *philo, t_fork *forks, long i, int nb_philo)
{
	int	j;

	if (i == nb_philo - 1)
		j = 0;
	else
		j = i + 1;
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[j];
	}
	else
	{
		philo->left_fork = &forks[j];
		philo->right_fork = &forks[i];
	}
}
