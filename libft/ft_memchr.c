/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:59:15 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/10 14:00:14 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int n, size_t size)
{
	unsigned char	*mb;

	mb = (unsigned char *) memoryBlock;
	while (size--)
	{
		if (*mb == (unsigned char)n)
			return (mb);
		mb++;
	}
	return (0);
}
