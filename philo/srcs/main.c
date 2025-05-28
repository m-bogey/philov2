/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:18:52 by mbogey            #+#    #+#             */
/*   Updated: 2025/05/29 01:50:37 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		check;
	t_table	table;

	check = 0;
	if (parsing(argc, argv) == -1)
		return (1);
	check = init(&table, argc, argv);
	if (check == -2)
		return (1);
	if (table.nb_philo == 0 || table.time_to_die == 0 || table.time_to_eat == 0
		|| table.time_to_sleep == 0 || table.nb_meals == 0)
	{
		printf("Error: bad args\n");
		check = -1;
	}
	if (check != -1)
		start_simulation(&table);
	clean(&table);
	return (0);
}
