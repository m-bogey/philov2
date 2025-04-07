#include "philo.h"

long	getime(t_table *table)
{
	long			t;
	long			res;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (table->start_time == -1)
		return (t);
	res = t - table->start_time;
	return (res);
}