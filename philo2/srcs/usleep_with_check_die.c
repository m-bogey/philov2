/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_with_check_die.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:49 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/12 19:25:41 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_with_check_die(long usec, t_table *table)
{
	long			t;
	struct timeval	start;
	struct timeval	end;

	t = 0;
	gettimeofday(&start, NULL);
	while (t < usec)
	{
		pthread_mutex_lock(&table->mutex_end.m);
		if (table->end_simulation == true)
		{
			pthread_mutex_unlock(&table->mutex_end.m);
			break ;
		}
		pthread_mutex_unlock(&table->mutex_end.m);
		usleep(50);
		gettimeofday(&end, NULL);
		t = (end.tv_sec - start.tv_sec) * 1000000
			+ (end.tv_usec - start.tv_usec);
	}
}
