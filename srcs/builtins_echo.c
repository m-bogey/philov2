/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:29:23 by mbogey            #+#    #+#             */
/*   Updated: 2024/05/09 01:54:16 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	echo(t_minishell *ms)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (ms->arg[1])
	{
		if (ms->arg[1][0] == '-' && ms->arg[1][1] == 'n')
		{
			i++;
			n = 1;
		}
	}
	while (ms->arg[i])
	{
		ft_printf("%s", ms->arg[i]);
		i++;
		if (i < ms->nb_arg)
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}
