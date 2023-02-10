/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:56:25 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/16 12:49:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (dst > src)
			((char *)dst)[len - i - 1] = ((char *)src)[len - i - 1];
		else
			((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
