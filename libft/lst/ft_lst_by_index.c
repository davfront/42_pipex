/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_by_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:15:39 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/12 11:33:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_by_index(t_list *lst, int i)
{
	t_list	*node;
	int		size;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	if (i < 0 || i > size - 1)
		return (NULL);
	node = lst;
	while (node->next && i > 0)
	{
		node = node->next;
		i--;
	}
	return (node);
}
