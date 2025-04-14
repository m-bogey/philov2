/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_init_mutex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:29 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/14 16:12:00 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_init_mutex(t_my_mutex *my_mutex)
{
	my_mutex->m_init = 0;
	if (pthread_mutex_init(&my_mutex->m, NULL) != 0)
		return (-1);
	my_mutex->m_init = 1;
	return (0);
}

int	safe_init_fork(t_fork *f)
{
	f->init = 0;
	if (pthread_mutex_init(&f->fork, NULL) != 0)
		return (-1);
	f->init = 1;
	f->can_use = true;
	return (0);
}
