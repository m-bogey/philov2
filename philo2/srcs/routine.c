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
	//usleep_with_check_die(time_think, philo->table);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//attendre tout les philos
	//voir le temps
	usleep(500);
	if (philo->id % 2 == 0)
	{
		print_mutex(philo, " is thinking\n");
		usleep(50);
	}
	while (1)
	{
		if (philo->table->end_simulation == true)
			break ;
		if (philo->full == true)
			break;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static void	eating(t_philo *philo)
{
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
			
			philo->time_last_meal = getime(philo->table);
			print_mutex(philo, " is eating\n");
			usleep_with_check_die(philo->table->time_to_eat, philo->table);
			philo->count_meals++;
			if (philo->table->nb_meals < philo->count_meals
				&& philo->table->nb_meals > 0)
				philo->full = true; // voir si mutex

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
