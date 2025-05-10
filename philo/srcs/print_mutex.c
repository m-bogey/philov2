/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:11 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/10 16:25:38 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, char *str)
{
	long			time;

	pthread_mutex_lock(&philo->table->mutex_start_time.m);
	time = getime(philo->table);
	pthread_mutex_unlock(&philo->table->mutex_start_time.m);
	pthread_mutex_lock(&philo->table->mutex_print.m);
	pthread_mutex_lock(&philo->table->mutex_can_write.m);
	while (philo->table->last_time > time)
	{
		usleep(100);
		time = getime(philo->table);
	}
	philo->table->last_time = time;
	if (philo->table->can_write == true)
		printf("%ld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->mutex_can_write.m);
	pthread_mutex_unlock(&philo->table->mutex_print.m);
}
