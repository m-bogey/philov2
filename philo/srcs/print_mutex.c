/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:11 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/27 19:18:21 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->mutex_can_write.m);
	if (philo->table->can_write == true)
		printf("%ld %d %s", getime(philo->table), philo->id, str);
	pthread_mutex_unlock(&philo->table->mutex_can_write.m);
}

void	print_mutex_end(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->mutex_can_write.m);
	printf("%ld %d %s", getime(philo->table), philo->id, str);
	pthread_mutex_unlock(&philo->table->mutex_can_write.m);
}
