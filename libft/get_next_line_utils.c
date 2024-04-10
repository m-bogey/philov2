/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:21:00 by mbogey            #+#    #+#             */
/*   Updated: 2024/01/05 16:16:08 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cpy_s2(char *s2, char *s3, size_t *nb, size_t i);

size_t	ft_strlen_n(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strdup_gnl(char *s, size_t *nb)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen_n(s, '\n') + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		if (str[i] == '\n')
		{
			i++;
			*nb = i;
			break ;
		}
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *s2, size_t *nb)
{
	char	*s3;
	size_t	i;

	if (s1 == NULL)
		return (ft_strdup_gnl(s2, nb));
	s3 = malloc(sizeof(char) * (ft_strlen_n(s1, '\0')
				+ ft_strlen_n(s2, '\n') + 1));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	ft_cpy_s2(s2, s3, nb, i);
	free(s1);
	return (s3);
}

void	ft_cpy_s2(char *s2, char *s3, size_t *nb, size_t i)
{
	size_t	j;

	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		if (s3[i] == '\n')
		{
			i++;
			*nb = j + 1;
			break ;
		}
		j++;
		i++;
	}
	s3[i] = '\0';
}

void	*ft_memmove_gnl(void *dest, const void *s, ssize_t size)
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
	((char *)dest)[i] = 0;
	return (dest);
}
