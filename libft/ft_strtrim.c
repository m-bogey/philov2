/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:57:15 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/17 19:57:20 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_start(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_check_end(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (s1)
	{
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*t;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_check_start(s1, set);
	end = ft_check_end(s1, set);
	if (start > end)
	{
		t = (char *) malloc(1 * sizeof(char));
		if (!t)
			return (NULL);
		t[0] = '\0';
		return (t);
	}
	t = (char *)malloc((end - start + 1) * sizeof(char));
	if (!t)
		return (NULL);
	ft_strlcpy(t, s1 + start, end - start + 1);
	return (t);
}
