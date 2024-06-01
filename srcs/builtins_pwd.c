/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:35:15 by mbogey            #+#    #+#             */
/*   Updated: 2024/05/07 19:35:16 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	pwd(t_err *err)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf != NULL)
	{
		ft_printf("%s\n", buf);
		free(buf);
	}
	else
		perror("getcwd");
	err->err = 0;
}
