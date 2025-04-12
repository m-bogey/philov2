/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_begin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:55 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/12 19:19:57 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	wait_for_begin(t_table *table)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&table->mutex_ready.m);
	if (table->philos_ready == true)
		res = true;
	pthread_mutex_unlock(&table->mutex_ready.m);
	return (res);
}
