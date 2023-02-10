/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:47:42 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/16 14:03:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	len_s;
	size_t	i0;
	size_t	i;

	if (!s)
		return (NULL);
	i0 = (size_t)start;
	len_s = ft_strlen(s);
	if (len_s <= i0)
		len = 0;
	else if (len_s < len + i0)
		len = len_s - i0;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i0 + i < len_s && i < len)
	{
		dest[i] = s[i0 + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
