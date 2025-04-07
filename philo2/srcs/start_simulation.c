#include "philo.h"

void	*check_end(void *arg)
{
	t_table *table;
	int		i;

	table = (t_table *)arg;
	//check si tout les philo run
	usleep(500);
	while (1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (check_philo(table->philos + i) == true)
			{
				table->end_simulation = true;
				print_mutex(table->philos, " died\n");
				break ;
			}
		}
		usleep(10);
	}

	return (NULL);
}

void	start_simulation(t_table *table)
{
	int i;

    i = 0;
    //gerer 0 nb meal : arg 5
    // gerer 1 philo
    while (i < table->nb_philo)
    {
        pthread_create(&table->philos[i].id_thread, NULL, &routine, &table->philos[i]);
        i++;
    }
    table->start_time = getime(table);
	
	pthread_create(&table->check_philos, NULL,
		&check_end, table);

    i = 0;
    while (i < table->nb_philo)
	{
        pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
	pthread_join(table->check_philos, NULL);
}



//pthread_create(&table->tables[i].thread_id, NULL, &routine, &table->tables[i]);