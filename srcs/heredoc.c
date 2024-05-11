/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:38:49 by tcoze             #+#    #+#             */
/*   Updated: 2024/04/18 14:56:23 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1[0] == '\0' && s2[0] == '\0')
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

int	heredoc(t_minishell *ms)
{
	char	*line;

	line = NULL;
	line = readline("heredoc> ");
	ms->heredoc = ft_strdup("");
	while (ft_strcmp(line, ms->in[0].str) != 0)
	{
		ms->heredoc = ft_strjoin(ms->heredoc, line);
		ms->heredoc = ft_strjoin(ms->heredoc, "\n");
		free(line);
		line = readline("heredoc> ");
	}
	temp_file(ms);
	ms->temp_fd = open(ms->temp_name, O_CREAT | O_RDWR | O_EXCL, 0600);
	ft_putstr_fd(ms->heredoc, ms->temp_fd);
	close(ms->temp_fd);
	ms->in[0].str = ms->temp_name;
	ms->in[0].type = 2;
	return (0);
}

int ft_abs(int num)
{
	if (num < 0)
		num = num * (-1);
	return (num);
}

int temp_file(t_minishell *ms)
{
	int		fd;
	int		i;
	char	buf[6];

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	ms->temp_name = ft_strdup("/tmp/minishell-thd.000000");
	if (read(fd, buf, 6) == -1)
		return (-1);
	while (i < 6)
	{
		ms->temp_name[19 + i] = ALNUM[ft_abs(buf[i] % 62)];
		i++;
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}
