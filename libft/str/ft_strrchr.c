/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:00:51 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/21 09:41:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s2;

	s2 = (char *)s + ft_strlen(s);
	while (s2 >= s)
	{
		if (*s2 == (char)c)
			return (s2);
		s2--;
	}
	return (NULL);
}
