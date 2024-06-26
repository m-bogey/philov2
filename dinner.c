#include "philo.h"

void	think(t_philo *philo)
{
	long	time;

	time = gettime(philo->table);
	printf("%ld %d is thinking\n", time, philo->id);
}

void    eat(t_philo *philo)
{
    long    time;

	time = gettime(philo->table);
	pthread_mutex_lock(&philo->left_fork->fork);
    printf("%ld %d has taken left fork\n", time, philo->id);
    pthread_mutex_lock(&philo->right_fork->fork);
    printf("%ld %d has taken right fork\n", time, philo->id);
    usleep(philo->table->time_to_eat);
	printf("%ld %d is eating\n", time, philo->id);
	philo->meals_counter++;
	if (philo->meals_counter >= philo->table->nbr_limit_meals
		&& philo->table->nbr_limit_meals != -1)
		philo->full = true;
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

void	sleeping(t_philo *philo)
{
	long	time;

	time = gettime(philo->table);
	usleep(philo->table->time_to_sleep);
	printf("%ld %d is sleeping\n", time, philo->id);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	while (1)
	{
	//	if (philo->full)
	//		break ;
		think(philo);
		eat(philo);
		if (philo->full == true)
			break;
		sleeping(philo);
	}

    return (NULL);
}

void    dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->nbr_limit_meals == 0)
        return ;
    else if (table->philo_nbr == 1)
        ;//TODO
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