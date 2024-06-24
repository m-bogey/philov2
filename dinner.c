#include "philo.h"

pthread_mutex_t test;

void    *routine(void *arg)
{
    t_philo *philo;
    long    time;

    philo = (t_philo *)arg;
    printf("salut\n");
  //  wait_all_threads();//TODO
	while (1)
	{
	//	if (philo->full)
	//		break ;
        time = gettime(philo->table);
  //      pthread_mutex_lock(&test);
        if (&philo->left_fork->fork && &philo->right_fork->fork)
        {
        pthread_mutex_lock(&philo->left_fork->fork);
        printf("%ld %d has taken left fork\n", time, philo->id);
        pthread_mutex_lock(&philo->right_fork->fork);
        printf("%ld %d has taken right fork\n", time, philo->id);
        usleep(philo->table->time_to_eat);
		printf("%ld %d is eating\n", time, philo->id);
        pthread_mutex_unlock(&philo->right_fork->fork);
        pthread_mutex_unlock(&philo->left_fork->fork);
        }
        time = gettime(philo->table);
        usleep(philo->table->time_to_sleep);
        printf("%ld %d is sleeping\n", time, philo->id);
    //    pthread_mutex_unlock(&test);
	}

    return (NULL);
}
void    dinner_start(t_table *table)
{
    int i;

    i = -1;
    pthread_mutex_init(&test, NULL);
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

    pthread_mutex_destroy(&test);
}