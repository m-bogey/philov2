#include "philo.h"

void	safe_init_mutex(t_table *table, t_my_mutex *my_mutex)
{
	my_mutex->m_init = 0;
	if (pthread_mutex_init(&my_mutex->m, NULL) != 0)
		exit_clean(table);
	my_mutex->m_init = 1;
}

void	safe_init_fork(t_table *table, t_fork *f)
{
	f->init = 0;
	if (pthread_mutex_init(&f->fork, NULL) != 0)
		exit_clean(table);
	f->init = 1;
	f->can_use = true;
}
