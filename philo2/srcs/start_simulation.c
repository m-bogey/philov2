#include "philo.h"

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].id_thread, NULL, &routine, &table->philos[i]);
		i++;
	}
	table->start_time = getime(table);

	pthread_create(&table->check_philos, NULL,
		&check_end_simulation, table);

	pthread_mutex_lock(&table->mutex_ready);
	table->philos_ready = true;
	pthread_mutex_unlock(&table->mutex_ready);

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
	pthread_join(table->check_philos, NULL);
}
