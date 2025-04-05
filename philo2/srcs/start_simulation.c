#include "philo.h"
#include <stdio.h>

void *mafonction(void *arg)
{
	int i = *((int *)arg);

	printf("Je suis le thread numéro %d\n", i);
	return (NULL);
}

void	start_simulation(t_table *table)
{
	(void)table;
	int	i;

	i = 0;

    pthread_t threads[2];  // Tableau de threads
    int param1 = 1, param2 = 2;  // Paramètres pour les threads

    // Création des deux threads
    pthread_create(&threads[0], NULL, mafonction, &param1);
    pthread_create(&threads[1], NULL, mafonction, &param2);

    // Attendre que les deux threads se terminent
    pthread_join(threads[0], NULL);  // Attendre le premier thread
    pthread_join(threads[1], NULL);  // Attendre le deuxième thread

    printf("Tous les threads ont terminé\n");

	//while (i < table->nb_table)
		//pthread create
}



//pthread_create(&table->tables[i].thread_id, NULL, &routine, &table->tables[i]);