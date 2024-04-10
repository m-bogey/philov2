/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:24:59 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/10 15:25:01 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	i = 0;
	while ((first[i] || second[i]) && i < len)
	{
		if (first[i] != second[i])
			return ((unsigned char)(first[i]) - (unsigned char)(second[i]));
		i++;
	}
	return (0);
}
