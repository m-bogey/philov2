/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:20:58 by mbogey            #+#    #+#             */
/*   Updated: 2024/05/16 19:53:39 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static int	get_pwd(t_li_line *li_env, char *str, int size)
{
	char	*new_oldpwd;

	while (li_env)
	{
		if (ft_strncmp(li_env->token.str, str, size) == 0)
		{
			new_oldpwd = getcwd(NULL, 0);
			if (new_oldpwd == NULL)
				return (-2);
			new_oldpwd = ft_strjoin(str, new_oldpwd);
			if (new_oldpwd == NULL)
				return (-1);
			free(li_env->token.str);
			li_env->token.str = ft_strdup(new_oldpwd);
			free(new_oldpwd);
			if (li_env->token.str == NULL)
				return (-1);
		}
		li_env = li_env->next;
	}
	return (0);
}

int	change_directory(t_minishell *ms, t_li_line *li_env, t_err *err)
{
	char	*str;

	if (get_pwd(li_env, "OLDPWD=", 7) == -1)
		return (-1);
	str = getenv("HOME");
	if (ms->arg[1] == NULL)
	{
		if (chdir(str) == -1)
			return (-1);
		if (get_pwd(li_env, "PWD=", 4) == -1)
			return (-1);
		return (0);
	}
	if (chdir(ms->arg[1]) == 0)
	{
		if (get_pwd(li_env, "PWD=", 4) == -1)
			return (-1);
	}
	else
	{
		perror("cd");
		return (-1);
	}
	err->err = 0;
	return (0);
}
