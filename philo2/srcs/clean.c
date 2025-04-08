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
