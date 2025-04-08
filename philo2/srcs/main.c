#include "philo.h"

int	main(int argc, char **argv)
{
	t_table table;

	if (parsing(argc, argv) == -1)
		return (1);
	init(&table, argc, argv);
	start_simulation(&table);
	clean(&table);
	return (0);
}
