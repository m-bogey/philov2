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
		safe_init_fork(table, &table->forks[i]);
		safe_init_mutex(table, &table->philos[i].mutex_full);
		safe_init_mutex(table, &table->philos[i].mutex_time_last_meal);
		i++;
	}
	safe_init_mutex(table, &table->mutex_print);
	safe_init_mutex(table, &table->mutex_ready);
	safe_init_mutex(table, &table->mutex_end);
	safe_init_mutex(table, &table->mutex_start_time);
	safe_init_mutex(table, &table->mutex_can_write);
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
