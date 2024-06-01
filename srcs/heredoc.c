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

int	heredoc(t_minishell *ms, int i)
{
	char	*line;

	dprintf(2, "VRAI MOT DE FIN DU HEREDOC : %s\n", ms->in[i].str);
	line = NULL;
	init_sig();
	temp_file(ms, i);
	ms->temp_fd = open(ms->temp_name[i], O_CREAT | O_RDWR | O_EXCL, 0600);
	line = readline("heredoc> ");
	if (line == NULL)
		return (1);
	if (g_sig == SIGINT)
		return (2);
	ms->heredoc[i] = ft_strdup("");
	while (ft_strcmp(line, ms->in[i].str) != 0)
	{
		ms->heredoc[i] = ft_strjoin(ms->heredoc[i], line);
		ms->heredoc[i] = ft_strjoin(ms->heredoc[i], "\n");
		free(line);
		line = readline("heredoc> ");
		if (line == NULL)
		{
			ft_putstr_fd(ms->heredoc[i], ms->temp_fd);
			close(ms->temp_fd);
			ms->in[0].str = ms->temp_name[i];
			return (1);
		}
		if (g_sig == SIGINT)
			return (2);
	}
	dprintf(2, "STRING DE CON : \n%s\n", ms->heredoc[i]);
	ft_putstr_fd(ms->heredoc[i], ms->temp_fd);
	close(ms->temp_fd);
	ms->in[i].str = ms->temp_name[i];
	ms->in[i].type = 2; // A VOIR SI ON DOIT PAS LE LAISSER EN 4 POUR EXPAND
	return (0);
}

int ft_abs(int num)
{
	if (num < 0)
		num = num * (-1);
	return (num);
}

int temp_file(t_minishell *ms, int i)
{
	int		fd;
	int		j;
	char	buf[6];

	j = 0;
	fd = open("/dev/urandom", O_RDONLY);
	ms->temp_name[i] = ft_strdup("/tmp/minishell-thd.000000");
	if (read(fd, buf, 6) == -1)
		return (-1);
	while (j < 6)
	{
		ms->temp_name[i][19 + j] = ALNUM[ft_abs(buf[j] % 62)];
		j++;
	}
	if (close(fd) == -1)
		return (-1);
	dprintf(2, "NOM DE FICHIER TEMPORAIRE : %s\n", ms->temp_name[i]);
	return (0);
}