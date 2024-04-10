/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:10:26 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/18 12:10:29 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_intmin(void)
{
	char	*tab;

	tab = (char *) malloc ((12) * sizeof(char));
	if (!tab)
		return (0);
	tab[0] = '-';
	tab[1] = '2';
	tab[2] = '1';
	tab[3] = '4';
	tab[4] = '7';
	tab[5] = '4';
	tab[6] = '8';
	tab[7] = '3';
	tab[8] = '6';
	tab[9] = '4';
	tab[10] = '8';
	tab[11] = '\0';
	return (tab);
}

static char	*ft_iszero(void)
{
	char	*tab;

	tab = (char *) malloc ((2) * sizeof(char));
	if (!tab)
		return (0);
	tab[0] = '0';
	tab[1] = '\0';
	return (tab);
}

static int	ft_compt_int(int n)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_filling_tab(int i, char *tab, int n, int neg)
{
	while (i >= 0)
	{
		tab[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	if (neg == 1)
		tab[0] = '-';
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		i;
	int		neg;

	neg = 0;
	i = 0;
	if (n == -2147483648)
		return (ft_intmin());
	if (n == 0)
		return (ft_iszero());
	if (n < 0)
	{
		n *= (-1);
		neg = 1;
	}
	i = ft_compt_int(n) + i + neg;
	tab = ft_calloc((i + 1) * sizeof(char), 1);
	if (!tab)
		return (0);
	i--;
	return (ft_filling_tab(i, tab, n, neg));
}
