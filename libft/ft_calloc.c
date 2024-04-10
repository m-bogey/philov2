/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:27:12 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/15 14:27:14 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*p;
	size_t	count;

	count = elementCount * elementSize;
	if (count != 0 && count / elementSize != elementCount)
		return (NULL);
	p = (void *)malloc(count);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count);
	return (p);
}
