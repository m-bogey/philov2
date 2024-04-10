/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:03:49 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/23 17:03:53 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*prev;

	if (!(*lst) || !del || !lst)
		return ;
	prev = *lst;
	while ((*lst))
	{
		prev = (*lst)->next;
		(del)((*lst)->content);
		free(*lst);
		*lst = prev;
	}
	*lst = NULL;
}
