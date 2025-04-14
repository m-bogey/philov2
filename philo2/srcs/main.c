/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:18:52 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/14 16:14:35 by mbogey           ###   ########.fr       */
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
	if (check != -1)
		start_simulation(&table);
	clean(&table);
	return (0);
}
