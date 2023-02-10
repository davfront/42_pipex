/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:58 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/14 14:44:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*char_s;
	char	char_c;
	size_t	i;

	char_s = (char *)s;
	char_c = (char)c;
	i = 0;
	while (i < n)
	{
		if (char_s[i] == char_c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
