/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:19:01 by mbogey            #+#    #+#             */
/*   Updated: 2025/04/12 19:19:03 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_nb_arg(int argc);
static int	check_int(int argc, char **argv);
static int	check_int_max(char *str);

int	parsing(int argc, char **argv)
{
	if (check_nb_arg(argc) == -1)
		return (-1);
	if (check_int(argc, argv) == -1)
		return (-1);
	return (0);
}

static int	check_nb_arg(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Error: need 4 or 5 argurments \n", 31);
		return (-1);
	}
	return (0);
}

static int	check_int(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write(2, "Error: you can write only positiv numbers !\n", 44);
				return (-1);
			}
			j++;
			if (j == 10)
				if (check_int_max(argv[i]) == -1)
					return (-1);
		}
		i++;
	}
	return (0);
}

static size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	check_int_max(char *str)
{
	size_t	size_str;
	int		i;
	bool	safe;

	safe = false;
	size_str = ft_strlen(str);
	i = 0;
	if (size_str > 10)
		return (write(2, "Error: arg less than 10 chars !\n", 32), -1);
	if (size_str == 10)
	{
		while (str[i])
		{
			if (str[i] < TESTINTMAX[i])
				safe = true;
			if (str[i] > TESTINTMAX[i] && safe == false)
			{
				write(2, "Error: nb > int max !\n", 22);
				return (-1);
			}
			i++;
		}
	}
	return (0);
}
