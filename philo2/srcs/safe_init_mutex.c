/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_init_mutex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:29 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/12 19:19:31 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_init_mutex(t_table *table, t_my_mutex *my_mutex)
{
	my_mutex->m_init = 0;
	if (pthread_mutex_init(&my_mutex->m, NULL) != 0)
		exit_clean(table);
	my_mutex->m_init = 1;
}

void	safe_init_fork(t_table *table, t_fork *f)
{
	f->init = 0;
	if (pthread_mutex_init(&f->fork, NULL) != 0)
		exit_clean(table);
	f->init = 1;
	f->can_use = true;
}
