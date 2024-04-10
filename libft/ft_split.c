/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:41:53 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/22 12:41:57 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **tab, long int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

static long int	ft_count_word(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	i = 1;
	nb = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			nb++;
		i++;
	}
	if (s[ft_strlen(s) - 1] == c)
		nb--;
	return (nb + 1);
}

static char	**fill_array(char const *s, char c, char **tab)
{
	long int	j;
	size_t		start;
	size_t		end;

	start = 0;
	j = 0;
	while (s[start] && j < ft_count_word((char *)s, c))
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		tab[j] = ft_substr((char *)s, start, end - start);
		if (!tab[j])
			return (ft_free(tab, j));
		start = end;
		j++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(ft_count_word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (0);
	tab = fill_array((char *)s, c, tab);
	return (tab);
}
