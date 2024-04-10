/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:05:03 by mbogey            #+#    #+#             */
/*   Updated: 2024/03/19 14:20:24 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n, size_t *count)
{
	if (n == INT_MIN)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		*count = *count + 11;
		return (0);
	}
	if (n < 0)
	{
		if (ft_putchar('-', count) == -1)
			return (-1);
		n *= (-1);
	}
	if (n >= 10)
		ft_putnbr(n / 10, count);
	if (ft_putchar((n % 10) + '0', count) == -1)
		return (-1);
	return (0);
}
