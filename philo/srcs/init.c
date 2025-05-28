/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:18:45 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/15 02:01:49 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		other_init(t_table *table);
static int		init_mutex(t_table *table);
static void		init_philo(t_table *table);
static void		what_fork(t_philo *philo, t_fork *forks, long i, int nb_philo);

int	init(t_table *table, int argc, char **argv)
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
	table->philos = NULL;
	table->forks = NULL;
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (-2);
	table->forks = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->forks)
	{
		free(table->philos);
		return (-2);
	}
	if (init_mutex(table) == -1)
		return (-1);
	init_philo(table);
	return (0);
}

static void	other_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->forks[i].init = 0;
		table->philos[i].mutex_full.m_init = 0;
		table->philos[i].mutex_time_last_meal.m_init = 0;
		i++;
	}
	table->mutex_ready.m_init = 0;
	table->mutex_end.m_init = 0;
	table->mutex_start_time.m_init = 0;
	table->mutex_can_write.m_init = 0;
	table->start_time = -1;
	table->philos_ready = false;
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	other_init(table);
	while (i < table->nb_philo)
	{
		if (safe_init_fork(&table->forks[i]) == -1)
			return (-1);
		if (safe_init_mutex(&table->philos[i].mutex_full) == -1)
			return (-1);
		if (safe_init_mutex(&table->philos[i].mutex_time_last_meal) == -1)
			return (-1);
		i++;
	}
	if (safe_init_mutex(&table->mutex_ready) == -1)
		return (-1);
	if (safe_init_mutex(&table->mutex_end) == -1)
		return (-1);
	if (safe_init_mutex(&table->mutex_start_time) == -1)
		return (-1);
	if (safe_init_mutex(&table->mutex_can_write) == -1)
		return (-1);
	return (0);
}

static void	init_philo(t_table *table)
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

static void	what_fork(t_philo *philo, t_fork *forks, long i, int nb_philo)
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
