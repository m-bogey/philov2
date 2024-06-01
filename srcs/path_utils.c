/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:59:31 by mbogey            #+#    #+#             */
/*   Updated: 2024/03/05 18:59:33 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static size_t	strlen_space(char *s1);

void	init_index(t_join *index)
{
	index->i = 0;
	index->j = 0;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	t_join	index;

	if (!s1 || !s2)
		return (0);
	init_index(&index);
	res = malloc(sizeof(char) * (ft_strlen(s1) + strlen_space(s2) + 2));
	if (!res)
		return (NULL);
	while (s1[index.i])
	{
		res[index.i] = s1[index.i];
		index.i++;
	}
	res[index.i] = '/';
	index.i++;
	while (s2[index.j] && s2[index.j] != ' ')
	{
		res[index.i] = s2[index.j];
		index.i++;
		index.j++;
	}
	res[index.i] = '\0';
	free (s1);
	return (res);
}

static size_t	strlen_space(char *s1)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != ' ')
		i++;
	return (i);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
