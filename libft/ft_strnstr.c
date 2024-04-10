/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:14:57 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/11 16:15:02 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	e;
	size_t	j;

	i = 0;
	e = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && len-- > 0)
	{
		j = i;
		while (big[j] == little[e] && e <= len)
		{
			if (little[e + 1] == '\0')
				return ((char *)big + i);
			j++;
			e++;
		}
		e = 0;
		i++;
	}
	return (NULL);
}
