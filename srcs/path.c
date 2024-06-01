/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:32:48 by mbogey            #+#    #+#             */
/*   Updated: 2024/03/05 20:32:51 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int		search_path(char **envp);
static char		*check_slash(char *str);
static char		*found_slash(char *str);
static void		init_cmd_path(t_path *p, char *ag, char **envp);

char	*cmd_path(char *ag, char **envp, t_err *err)
{
	t_path	p;

	p.path = check_slash(ag);
	if (p.path != NULL)
		return (p.path);
	init_cmd_path(&p, ag, envp);
	while (p.tab_path[p.p])
	{
		if (access(p.tab_path[p.p], X_OK) == 0)
		{
			p.path = ft_strdup(p.tab_path[p.p]);
			break ;
		}
		p.p++;
	}
	if (p.path == NULL)
	{
		write (2, "command not found\n", 18);
		err->err = 127;
		ft_printf("return value cmd_path : %d\n", err->err);
	}
	ft_free_tab(p.tab_path);
	return (p.path);
}

static int	search_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
				&& envp[i][3] == 'H' && envp[i][4] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*check_slash(char *str)
{
	size_t	i;
	size_t	y;
	char	*s;

	s = NULL;
	i = 0;
	y = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '/')
			y = 1;
		i++;
	}
	if (y != 0)
		s = found_slash(str);
	return (s);
}

static char	*found_slash(char *str)
{
	char	*s;
	size_t	j;

	j = 0;
	while (str[j] && str[j] != ' ')
		j++;
	s = malloc(sizeof(char) * (j + 1));
	if (s == NULL)
		return (NULL);
	j = 0;
	while (str[j] && str[j] != ' ')
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

void	init_cmd_path(t_path *p, char *ag, char **envp)
{
	p->p = search_path(envp);
	if (p->p == -1)
	{
		write(2, "No such file or directory\n", 26);
		exit(EXIT_FAILURE);
	}
	p->tab_path = ft_split(envp[p->p] + 5, ':');
	if (p->tab_path == NULL)
		exit(EXIT_FAILURE);
	p->p = 0;
	while (p->tab_path[p->p])
	{
		p->tab_path[p->p] = ft_strjoin_free(p->tab_path[p->p], ag);
		if (p->tab_path[p->p] == NULL)
		{
			ft_free_tab(p->tab_path);
			exit(EXIT_FAILURE);
		}
		p->p++;
	}
	p->p = 0;
}
