/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:15:48 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/18 14:15:50 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*node;
	t_list	*node2;

	if (!lst || !f || !del)
		return (NULL);
	lst2 = NULL;
	node = lst;
	while (node)
	{
		node2 = ft_lstnew((*f)(node->content));
		if (!node2)
		{
			ft_lstclear(&lst2, del);
			return (NULL);
		}
		ft_lstadd_back(&lst2, node2);
		node = node->next;
	}
	return (lst2);
}
