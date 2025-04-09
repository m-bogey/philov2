#include "philo.h"

void	usleep_with_check_die(long usec, t_table *table)
{
	(void)table;

	long			t;
	struct timeval	start;
	struct timeval	end;

	t = 0;
	gettimeofday(&start, NULL);
	while (t < usec)
	{
		pthread_mutex_lock(&table->mutex_end_sim);
		if (table->end_simulation == true)
			break ;
		pthread_mutex_unlock(&table->mutex_end_sim);
		// quitter si simulation fini
		usleep(50);
		gettimeofday(&end, NULL);
		t = (end.tv_sec - start.tv_sec) * 1000000
			+ (end.tv_usec - start.tv_usec);
	}
}
