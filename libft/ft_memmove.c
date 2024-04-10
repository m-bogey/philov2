/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:07:24 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/12 22:16:22 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *s, size_t size)
{
	size_t	i;

	if (!s && !dest)
		return (NULL);
	if (dest > s)
	{
		i = size - 1;
		while (size--)
		{
			((char *)dest)[i] = ((char *) s)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (size--)
		{
			((char *)dest)[i] = ((char *)s)[i];
			i++;
		}
	}
	return (dest);
}
