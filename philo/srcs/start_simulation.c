/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:39 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/27 17:52:15 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_philo(t_table *table);

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_mutex(philo, " has taken a fork\n");
	usleep(philo->table->time_to_die);
	print_mutex(philo, " died\n");
	return (NULL);
}

int	special_simulation(t_table *table)
{
	table->start_time = getime(table);
	if (table->nb_philo == 0 || table->nb_meals == 0)
		return (1);
	if (table->nb_philo == 1)
	{
		pthread_create(&table->philos[0].id_thread, NULL,
			&one_philo, &table->philos[0]);
		pthread_join(table->philos[0].id_thread, NULL);
		return (1);
	}
	return (0);
}

void	clean_create_fail(t_table *table, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&table->mutex_can_write.m);
	table->can_write = false;
	pthread_mutex_unlock(&table->mutex_can_write.m);
	pthread_mutex_lock(&table->mutex_ready.m);
	table->philos_ready = true;
	pthread_mutex_unlock(&table->mutex_ready.m);
	pthread_mutex_lock(&table->mutex_end.m);
	table->end_simulation = true;
	pthread_mutex_unlock(&table->mutex_end.m);
	while (j < i)
	{
		pthread_join(table->philos[j].id_thread, NULL);
		j++;
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	if (special_simulation(table) == 1)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i].id_thread, NULL,
				&routine, &table->philos[i]) != 0)
		{
			clean_create_fail(table, i - 1);
			return ;
		}
		i++;
	}
	if (pthread_create(&table->check_philos, NULL,
			&check_end_simulation, table) != 0)
	{
		clean_create_fail(table, table->nb_philo);
		return ;
	}
	pthread_mutex_lock(&table->mutex_ready.m);
	table->philos_ready = true;
	pthread_mutex_unlock(&table->mutex_ready.m);
	join_philo(table);
}

int	join_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
	pthread_join(table->check_philos, NULL);
	return (0);
}
