/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:20 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/12 19:19:21 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo);
static void	sleeping(t_philo *philo);

static void	thinking(t_philo *philo)
{
/*	long time_think;

	if (philo->table->nb_philo % 2 == 0)
		time_think = 0;
	else
		time_think = philo->table->time_to_eat * 2
			- philo->table->time_to_sleep;
	if (time_think < 0)
		time_think = 0;*/
	print_mutex(philo, " is thinking\n");
	//usleep_with_check_die(10, philo->table);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	end_sim;
	bool	is_full;

	philo = (t_philo *)arg;
	while (wait_for_begin(philo->table) == false)
		usleep(5);
	if (philo->id % 2 == 0)
	{
		print_mutex(philo, " is thinking\n");
		usleep(50);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex_end.m);
		end_sim = philo->table->end_simulation;
		pthread_mutex_unlock(&philo->table->mutex_end.m);
		if (end_sim == true)
			break ;
		pthread_mutex_lock(&philo->mutex_full.m);
		is_full = philo->full;
		pthread_mutex_unlock(&philo->mutex_full.m);
		if (is_full == true)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

// static bool	try_take_forks(t_philo *philo)
// {
// 	bool	left;
// 	bool	right;

// 	left = false;
// 	right = false;
// 	pthread_mutex_lock(&philo->left_fork->fork);
// 	if (philo->left_fork->can_use == true)
// 	{
// 		philo->left_fork->can_use = false;
// 		left = true;
// 	}
// 	pthread_mutex_unlock(&philo->left_fork->fork);
// 	if (left == false)
// 		return (false);

// 	pthread_mutex_lock(&philo->right_fork->fork);
// 	if (philo->right_fork->can_use == true)
// 	{
// 		philo->right_fork->can_use = false;
// 		right = true;
// 	}
// 	pthread_mutex_unlock(&philo->right_fork->fork);

// 	if (right == false)
// 	{
// 		pthread_mutex_lock(&philo->left_fork->fork);
// 		philo->left_fork->can_use = true;
// 		pthread_mutex_unlock(&philo->left_fork->fork);
// 		return (false);
// 	}
// 	print_mutex(philo, " has taken a fork\n");
// 	print_mutex(philo, " has taken a fork\n");
// 	return (true);
// }

static void	eating(t_philo *philo)
{
	// if (try_take_forks(philo) == false)
	// 	return ;
	// pthread_mutex_lock(&philo->mutex_time_last_meal.m);
	// philo->time_last_meal = getime(philo->table);
	// pthread_mutex_unlock(&philo->mutex_time_last_meal.m);

	// print_mutex(philo, " is eating\n");
	// usleep_with_check_die(philo->table->time_to_eat, philo->table);
	// philo->count_meals++;
	// if (philo->table->nb_meals < philo->count_meals
	// 	&& philo->table->nb_meals > 0)
	// {
	// 	pthread_mutex_lock(&philo->mutex_full.m);
	// 	philo->full = true;
	// 	pthread_mutex_unlock(&philo->mutex_full.m);
	// }
	// pthread_mutex_lock(&philo->left_fork->fork);
	// philo->left_fork->can_use = true;
	// pthread_mutex_unlock(&philo->left_fork->fork);

	// pthread_mutex_lock(&philo->right_fork->fork);
	// philo->right_fork->can_use = true;
	// pthread_mutex_unlock(&philo->right_fork->fork);
	
	// while (philo->left_fork->can_use != true)
	// 	usleep(10);
	
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->can_use == true)
	{
		philo->left_fork->can_use = false;
		print_mutex(philo, " has taken a fork\n");
		pthread_mutex_lock(&philo->right_fork->fork);
		if (philo->right_fork->can_use == true)
		{
			philo->right_fork->can_use = false;
			print_mutex(philo, " has taken a fork\n");
			
			pthread_mutex_lock(&philo->mutex_time_last_meal.m);
			philo->time_last_meal = getime(philo->table);
			pthread_mutex_unlock(&philo->mutex_time_last_meal.m);
			print_mutex(philo, " is eating\n");
			usleep_with_check_die(philo->table->time_to_eat, philo->table);
			philo->count_meals++;
			if (philo->table->nb_meals < philo->count_meals
				&& philo->table->nb_meals > 0)
			{
				pthread_mutex_lock(&philo->mutex_full.m);
				philo->full = true;
				pthread_mutex_unlock(&philo->mutex_full.m);
			}

			philo->right_fork->can_use = true;
		}
		pthread_mutex_unlock(&philo->right_fork->fork);
		philo->left_fork->can_use = true;
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
}

static void	sleeping(t_philo *philo)
{
	print_mutex(philo, " is sleeping\n");
	usleep_with_check_die(philo->table->time_to_sleep, philo->table);
}
