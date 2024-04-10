/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:08:36 by mbogey            #+#    #+#             */
/*   Updated: 2023/12/04 20:08:38 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsign(unsigned int nb, size_t *count)
{
	if (nb >= 10)
		ft_putunsign(nb / 10, count);
	if (ft_putchar((nb % 10) + '0', count) == -1)
		return (-1);
	return (0);
}
