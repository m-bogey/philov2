/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:17:27 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/10 15:17:29 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	e;
	size_t	i;
	size_t	q;

	e = 0;
	i = 0;
	while (dest[e] && e < size)
		e++;
	q = e;
	e = 0;
	while (dest[e])
		e++;
	while (src[i] && e < size - 1 && size != 0)
	{
		dest[e] = src[i];
		i++;
		e++;
	}
	dest[e] = '\0';
	return (ft_strlen(src) + q);
}
