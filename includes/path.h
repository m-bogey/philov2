/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:00:24 by mbogey            #+#    #+#             */
/*   Updated: 2024/03/05 19:00:27 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_path
{
	int		p;
	char	**tab_path;
	char	*path;
}				t_path;

typedef struct s_join
{
	int		i;
	int		j;
}				t_join;

char	*cmd_path(char *ag, char **envp);
void	ft_free_tab(char **tab);
char	*ft_strjoin_free(char *s1, char *s2);

#endif
