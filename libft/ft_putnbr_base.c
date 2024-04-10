/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:59:39 by mbogey            #+#    #+#             */
/*   Updated: 2023/12/04 19:59:42 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nb, char *base, size_t *count)
{
	if (nb >= ft_strlen_print(base))
		ft_putnbr_base(nb / ft_strlen_print(base), base, count);
	if (ft_putchar(base[nb % ft_strlen_print(base)], count) == -1)
		return (-1);
	return (0);
}
