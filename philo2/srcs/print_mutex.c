#include "philo.h"

void	print_mutex(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutex_start_time.m);
	time = getime(philo->table);
	pthread_mutex_unlock(&philo->table->mutex_start_time.m);
	pthread_mutex_lock(&philo->table->mutex_print.m);
	pthread_mutex_lock(&philo->table->mutex_can_write.m);
	if (philo->table->can_write == true)
		printf("%ld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->mutex_can_write.m);
	pthread_mutex_unlock(&philo->table->mutex_print.m);
}