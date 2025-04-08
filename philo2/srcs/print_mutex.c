#include "philo.h"

void	print_mutex(t_philo *philo, char *str)
{
	long	time;

	time = getime(philo->table);
	pthread_mutex_lock(&philo->table->mutex_print);
	if (philo->table->can_write == true)
		printf("%ld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->mutex_print);
}