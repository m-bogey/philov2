/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:10:26 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/10 19:13:59 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int value, size_t count)
{
	char	*str;

	str = p;
	while (count)
	{
		*str++ = (unsigned char)value;
		count--;
	}
	return (p);
}
