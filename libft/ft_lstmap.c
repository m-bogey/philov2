/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:20:19 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/24 13:20:23 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*list;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		cont = (*f)(lst->content);
		temp = ft_lstnew(cont);
		if (!temp)
		{
			(*del)(cont);
			ft_lstclear(&list, del);
			return (list);
		}
		ft_lstadd_back(&list, temp);
		lst = lst->next;
	}
	return (list);
}
