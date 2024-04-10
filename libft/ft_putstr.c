/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:07:12 by mbogey            #+#    #+#             */
/*   Updated: 2023/12/04 20:07:15 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s, size_t *count)
{
	int	i;

	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		*count = *count + 6;
		return (0);
	}
	i = 0;
	while (s[i])
		if (ft_putchar(s[i++], count) == -1)
			return (-1);
	return (i);
}
