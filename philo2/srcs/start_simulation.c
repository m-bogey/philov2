#include "philo.h"

int		special_simulation(t_table *table)
{
	if (table->nb_philo == 0 || table->nb_meals == 0)
		return (1);
	if (table->nb_philo == 1)
	{
		pthread_create(&table->philos[0].id_thread, NULL, &one_philo, &table->philos[0]);
		table->start_time = getime(table);
		pthread_join(&table->philos[0].id_thread, NULL);
	}
	return (0);
}

void	start_simulation(t_table *table)
{
	int	i;

	if (special_simulation(table) == 1)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].id_thread, NULL, &routine, &table->philos[i]);
		i++;
	}
	//pthread_mutex_lock(&table->mutex_time);
	table->start_time = getime(table);
	//pthread_mutex_unlock(&table->mutex_time);
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
