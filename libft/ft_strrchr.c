/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:30:18 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/10 16:06:38 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int n)
{
	long int	i;
	char		*s;

	i = 0;
	s = (char *)str;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)n)
			return (s + i);
		i--;
	}
	return (NULL);
}
