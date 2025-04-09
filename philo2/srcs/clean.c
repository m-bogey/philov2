#include "philo.h"

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->forks[i].init == 1)
			pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	if (table->mutex_print_init == 1)
		pthread_mutex_destroy(&table->mutex_print);
	if (table->mutex_ready_init == 1)
		pthread_mutex_destroy(&table->mutex_ready);
	if (table->mutex_end_init == 1)
		pthread_mutex_destroy(&table->mutex_end);
	if (table->mutex_meal_init == 1)
		pthread_mutex_destroy(&table->mutex_meal);
	if (table->mutex_full_init == 1)
		pthread_mutex_destroy(&table->mutex_full);
	if (table->mutex_time_init == 1)
		pthread_mutex_destroy(&table->mutex_time);
	if (table->mutex_end_sim_init == 1)
		pthread_mutex_destroy(&table->mutex_end);
	if (table->mutex_canwrite_init == 1)
		pthread_mutex_destroy(&table->mutex_canwrite);
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
