/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <mbogey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:29:23 by mbogey            #+#    #+#             */
/*   Updated: 2024/05/12 17:06:08 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	echo(t_minishell *ms, t_err *err)
{
	int	i;
	int	n;
	int y;

	n = 0;
	i = 1;
	y = 1;
	if (ms->arg[1])
	{
		if (ms->arg[1][0] == '-')
		{
			while (ms->arg[1][i] == 'n')
			{
				i++;
				n = 1;
			}
			y = 2;
			if (ms->arg[1][i] != ' ' && ms->arg[1][i] != '\0')
			{
				n = 0;
				y = 1;
			}
		}
	}
	while (ms->arg[y])
	{
		/*if (ms->arg[y][0] == '?')		SOUCIS EXPAND
		{
			ft_printf("%d", err->err);
			while(ms->arg[y][count])
				write(1, &ms->arg[y][count++], 1);
			y++;
			write(1, " ", 1);
		}
		else
		{*/
			ft_printf("%s", ms->arg[y]);
			y++;
			if (y < ms->nb_arg)
				write(1, " ", 1);
	//	}
	}
	if (n == 0)
		write(1, "\n", 1);
	err->err = 0;
}
