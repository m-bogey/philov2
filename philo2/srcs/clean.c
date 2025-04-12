/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:18:28 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/12 19:23:35 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_table(t_table *table)
{
	if (table->philos != NULL)
		free(table->philos);
	if (table->forks != NULL)
		free(table->forks);
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->forks[i].init == 1)
			pthread_mutex_destroy(&table->forks[i].fork);
		if (table->philos[i].mutex_full.m_init == 1)
			pthread_mutex_destroy(&table->philos[i].mutex_full.m);
		if (table->philos[i].mutex_time_last_meal.m_init == 1)
			pthread_mutex_destroy(&table->philos[i].mutex_time_last_meal.m);
		i++;
	}
	if (table->mutex_print.m_init == 1)
		pthread_mutex_destroy(&table->mutex_print.m);
	if (table->mutex_ready.m_init == 1)
		pthread_mutex_destroy(&table->mutex_ready.m);
	if (table->mutex_end.m_init == 1)
		pthread_mutex_destroy(&table->mutex_end.m);
	if (table->mutex_start_time.m_init == 1)
		pthread_mutex_destroy(&table->mutex_start_time.m);
	if (table->mutex_can_write.m_init == 1)
		pthread_mutex_destroy(&table->mutex_can_write.m);
	free_table(table);
}

void	exit_clean(t_table *table)
{
	clean(table);
	exit(1);
}
