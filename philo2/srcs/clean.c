#include "philo.h"

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->forks[i].init == 1)
			pthread_mutex_destroy(&table->forks[i].fork);
		if (table->philos[i].mutex_full.m_init == 1)
			pthread_mutex_destroy(&table->philos[i].mutex_full.m);
		if (table->philos[i].mutex_time_last_meal.m_init == 1)
			pthread_mutex_destroy(&table->philos[i].mutex_time_last_meal.m);
		i++;
	}
	if (table->mutex_print.m_init == 1)
		pthread_mutex_destroy(&table->mutex_print.m);
	if (table->mutex_ready.m_init == 1)
		pthread_mutex_destroy(&table->mutex_ready.m);
	if (table->mutex_end.m_init == 1)
		pthread_mutex_destroy(&table->mutex_end.m);
	if (table->mutex_start_time.m_init == 1)
		pthread_mutex_destroy(&table->mutex_start_time.m);
	if (table->mutex_can_write.m_init == 1)
		pthread_mutex_destroy(&table->mutex_can_write.m);
	if (table->philos != NULL)
		free(table->philos);
	if (table->forks != NULL)
		free(table->forks);
}

void	exit_clean(t_table *table)
{
	clean(table);
	exit(1);
}
