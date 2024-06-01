/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:52:34 by mbogey            #+#    #+#             */
/*   Updated: 2024/05/08 20:52:36 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char		*go_remove_quote(char *s);
static size_t	ft_strlen_quote(char *s);
static void		neg_line_quote(char **s, size_t i);
static void		pos_line_quote(char **s);

int	remove_quote(t_li_line *li)
{
	size_t	i;

	while (li->next)
	{
		i = 0;
		while (li->token.str[i])
		{
			if (li->token.str[i] == '\'' || li->token.str[i] == '\"')
			{
				li->token.str = go_remove_quote(li->token.str);
				if (li->token.str == NULL)
					return (-1);
				break ;
			}
			i++;
		}
		li = li->next;
	}
	return (0);
}

static char	*go_remove_quote(char *s)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	neg_line_quote(&s, i);
	new_s = malloc(sizeof(char) * ft_strlen_quote(s) + 1);
	if (new_s == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == '\'' || s[i] == '\"')
			i++;
		new_s[j] = s[i];
		i++;
		j++;
	}
	new_s[j] = '\0';
	pos_line_quote(&new_s);
	free(s);
	return (new_s);
}

static size_t	ft_strlen_quote(char *s)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	return (i - count);
}

static void	neg_line_quote(char **s, size_t i)
{
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
		{
			i++;
			while ((*s)[i] != '\'')
			{
				if ((*s)[i] == '\"')
					(*s)[i] *= -1;
				i++;
			}
		}
		if ((*s)[i] == '\"')
		{
			i++;
			while ((*s)[i] != '\"')
			{
				if ((*s)[i] == '\'')
					(*s)[i] *= -1;
				i++;
			}
		}
		i++;
	}
}

static void	pos_line_quote(char **s)
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] < 0)
			(*s)[i] *= -1;
		i++;
	}
}
