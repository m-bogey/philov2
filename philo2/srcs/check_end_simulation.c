#include "philo.h"

static bool	check_philo_die(t_philo *philo);

void	*check_end_simulation(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (wait_for_begin(table) == false)
		usleep(5);
	while (1)
	{
		pthread_mutex_lock(&table->mutex_end.m);
		if (table->end_simulation == true)
		{
			pthread_mutex_unlock(&table->mutex_end.m);
			break ;
		}
		pthread_mutex_unlock(&table->mutex_end.m);
		i = 0;
		while (i < table->nb_philo)
		{
			if (check_philo_die(table->philos + i) == true)
				break ;
			i++;
		}
		usleep(10);
	}
	return (NULL);
}

static bool	check_philo_die(t_philo *philo)
{
	long	t;

	pthread_mutex_lock(&philo->table->mutex_start_time.m);
	t = getime(philo->table);
	pthread_mutex_unlock(&philo->table->mutex_start_time.m);

	pthread_mutex_lock(&philo->mutex_time_last_meal.m);
	t = t - philo->time_last_meal;
	pthread_mutex_unlock(&philo->mutex_time_last_meal.m);
	if (t > philo->table->time_to_die / 1000)
	{
		pthread_mutex_lock(&philo->table->mutex_end.m);
		philo->table->end_simulation = true;
		pthread_mutex_unlock(&philo->table->mutex_end.m);
		print_mutex(philo->table->philos, " died\n");
		pthread_mutex_lock(&philo->table->mutex_can_write.m);
		philo->table->can_write = false;
		pthread_mutex_unlock(&philo->table->mutex_can_write.m);
		return (true);
	}
	return (false);
}
