/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:58:17 by mbogey            #+#    #+#             */
/*   Updated: 2023/12/04 19:58:20 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_p(unsigned long i, size_t *count)
{
	if (i >= 16)
		ft_putnbr_p(i / 16, count);
	if (i % 16 < 10)
	{
		if (ft_putchar(i % 16 + '0', count) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar(i % 16 + 'a' - 10, count) == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_p(unsigned long i, size_t *count)
{
	if (i == 0)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		*count = *count + 5;
		return (0);
	}
	if (write (1, "0x", 2) == -1)
		return (-1);
	*count = *count + 2;
	ft_putnbr_p(i, count);
	return (0);
}
