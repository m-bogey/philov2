/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:05:02 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/11 19:16:28 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *s, size_t size)
{
	char	*d;

	if (!s && !dest)
		return (NULL);
	d = (char *)dest;
	while (size)
	{
		*(char *)d = *(char *)s;
		d++;
		s++;
		size--;
	}
	return (dest);
}
