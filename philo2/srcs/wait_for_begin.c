#include "philo.h"

bool	wait_for_begin(t_table *table)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&table->mutex_ready);
	if (table->philos_ready == true)
		res = true;
	pthread_mutex_unlock(&table->mutex_ready);
	return (res);
}
