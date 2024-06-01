/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:04:06 by mbogey            #+#    #+#             */
/*   Updated: 2024/05/09 03:09:17 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

size_t	ft_strlen_egal(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	unset(t_li_line *li_env, t_minishell *ms, t_err *err)
{
	int	i;

	i = 0;
	while (li_env)
	{	
		while (ms->arg[i])
		{
			if (li_env->token.str[0] == '_')
				;
			else 
			{
				if (ft_strncmp(li_env->token.str, ms->arg[i],
				ft_strlen_egal(li_env->token.str)) == 0)
				li_env->token.str[0] = '\0';
			}
			i++;
		}
		i = 0;
		li_env = li_env->next;
	}
	err->err = 0;
}
