#include "philo.h"

// void	check_death_philo(t_philo *philo, long value)
// {
// 	long	i;

// 	i = 0;
// 	while (i < value)
// 	{
// 		if (philo->table->time_to_die < i)
// 		{
// 			printf("Philo mort");
// 			exit(0);
// 		}
// 		usleep(100);
// 		i = i + 100;
// 	}
// }

void	think(t_philo *philo)
{

	//philo->table->time = gettime(philo->table);

	safe_printf(philo, " is thinking.\n");
}

void	eat(t_philo *philo)
{
	long	time;

	time = gettime(philo->table);
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->is_available == true)
	{
		philo->left_fork->is_available = false;
		pthread_mutex_lock(&philo->table->mutex);
		time = gettime(philo->table);
	//	printf("time = %ld\n", time);
		printf("%ld %d has taken left fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->table->mutex);
		pthread_mutex_lock(&philo->right_fork->fork);
		if (philo->right_fork->is_available == true)
		{
			philo->right_fork->is_available = false;
			pthread_mutex_lock(&philo->table->mutex);
			printf("%ld %d has taken right fork\n", time, philo->id);
			pthread_mutex_unlock(&philo->table->mutex);
			time = gettime(philo->table);
			pthread_mutex_lock(&philo->table->mutex);
			printf("%ld %d is eating\n", time, philo->id);
			pthread_mutex_unlock(&philo->table->mutex);
			usleep(philo->table->time_to_eat);
			//check_death_philo(philo, philo->table->time_to_eat);
			philo->meals_counter++;
			if (philo->meals_counter >= philo->table->nbr_limit_meals
				&& philo->table->nbr_limit_meals != -1)
				philo->full = true;
			philo->right_fork->is_available = true;
		}
		pthread_mutex_unlock(&philo->right_fork->fork);
		philo->left_fork->is_available = true;
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	sleeping(t_philo *philo)
{
	long	time;

	time = gettime(philo->table);
	printf("%ld %d is sleeping\n", time, philo->id);
	usleep(philo->table->time_to_sleep);
	//check_death_philo(philo, philo->table->time_to_eat);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_init(&philo->table->mutex, NULL);
	while (1)
	{
		if (philo->full == true)
			break ;
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		return ;//TODO
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]);
	}
	table->start_simulation = gettime(table);
 //   pthread_mutex_lock(table->table_mutex);
   // sleep(10);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
}
