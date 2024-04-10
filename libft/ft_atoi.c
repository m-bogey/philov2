/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:49:33 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/11 10:49:39 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_long_max_or_min(int signe)
{
	if (signe == -1)
		return (LONG_MIN);
	return (LONG_MAX);
}

static long	ft_strtol(const char *p)
{
	long	nbr;
	int		i;
	int		signe;

	nbr = 0;
	i = 0;
	signe = 1;
	while ((p[i] >= 9 && p[i] <= 13) || p[i] == 32)
		i++;
	if (p[i] == '-' || p[i] == '+')
	{
		if (p[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(p[i]))
	{
		if (nbr != ((nbr * 10) + (p[i] - '0')) / 10)
			return (ft_long_max_or_min(signe));
		nbr = (nbr * 10) + (p[i] - '0');
		i++;
	}
	return (nbr * signe);
}

int	ft_atoi(const char *p)
{
	return ((int)ft_strtol(p));
}
