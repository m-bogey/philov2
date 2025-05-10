/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:18:10 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/10 16:36:29 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_philo_die(t_philo *philo);
static int	set_tab(t_table *table, int *i, int *count_full_philos);

void	*check_end_simulation(void *arg)
{
	t_table	*table;
	int		i;
	int		count_full_philos;

	count_full_philos = 0;
	table = (t_table *)arg;
	while (wait_for_begin(table) == false)
		usleep(50);
	while (1)
	{
		if (set_tab(table, &i, &count_full_philos) == 1)
			break ;
		while (i < table->nb_philo)
		{
			if (check_philo_die(table->philos + i) == true)
				break ;
			pthread_mutex_lock(&table->philos[i].mutex_full.m);
			if (table->philos[i].full == true)
				count_full_philos++;
			pthread_mutex_unlock(&table->philos[i].mutex_full.m);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

static bool	check_philo_die(t_philo *philo)
{
	long	t;

	pthread_mutex_lock(&philo->table->mutex_start_time.m);
	t = getime(philo->table);
	pthread_mutex_unlock(&philo->table->mutex_start_time.m);
	pthread_mutex_lock(&philo->mutex_time_last_meal.m);
	t = t - philo->time_last_meal;
	pthread_mutex_unlock(&philo->mutex_time_last_meal.m);
	if (t > philo->table->time_to_die / 1000)
	{
		pthread_mutex_lock(&philo->table->mutex_end.m);
		philo->table->end_simulation = true;
		pthread_mutex_unlock(&philo->table->mutex_end.m);
		usleep(1000);
		print_mutex(philo->table->philos, " died\n");
		pthread_mutex_lock(&philo->table->mutex_can_write.m);
		philo->table->can_write = false;
		pthread_mutex_unlock(&philo->table->mutex_can_write.m);
		return (true);
	}
	return (false);
}

static int	set_tab(t_table *table, int *i, int *count_full_philos)
{
	if (*count_full_philos == table->nb_philo)
	{
		pthread_mutex_lock(&table->mutex_end.m);
		table->end_simulation = true;
		pthread_mutex_unlock(&table->mutex_end.m);
		pthread_mutex_lock(&table->mutex_can_write.m);
		table->can_write = false;
		pthread_mutex_unlock(&table->mutex_can_write.m);
	}
	pthread_mutex_lock(&table->mutex_end.m);
	if (table->end_simulation == true)
	{
		pthread_mutex_unlock(&table->mutex_end.m);
		return (1);
	}
	pthread_mutex_unlock(&table->mutex_end.m);
	*i = 0;
	*count_full_philos = 0;
	return (0);
}
