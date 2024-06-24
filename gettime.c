#include "philo.h"

long	gettime(t_table *table)
{
	struct timeval tv;
	long	time;
	long	result;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (table->start_simulation == -1)
		return (time);
	result = time - table->start_simulation;
	return (result);
}