#include "philo.h"

static bool	check_philo_die(t_philo *philo)
{
	long	t;
	
	t = getime(philo->table) - philo->time_last_meal;
	if (t > philo->table->time_to_die / 1000)
	{
		philo->table->end_simulation = true;
		print_mutex(philo->table->philos, " died\n");
		philo->table->can_write = false;
		return (true);
	}
	return (false);
}

void	*check_end_simulation(void *arg)
{
	t_table *table;
	int		i;

	table = (t_table *)arg;
	//check si tout les philo run
	usleep(500);
	while (1)
	{
		if (table->end_simulation == true)
			break ;
		i = 0;
		while (i < table->nb_philo)
		{
			if (check_philo_die(table->philos + i) == true)
				break ;
		}
		usleep(10);
	}
	return (NULL);
}