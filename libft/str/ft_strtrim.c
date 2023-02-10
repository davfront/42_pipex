/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:15:21 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/16 14:07:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	trim_count(char const *s1, char const *set)
{
	size_t	n;
	size_t	len;
	size_t	i;

	n = 0;
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
	{
		i++;
		n++;
	}
	if (i + 1 < len)
	{
		i = len - 1;
		while (is_in_set(s1[i], set))
		{
			i--;
			n++;
		}
	}
	return (n);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1)
		return (0);
	size = ft_strlen(s1) - trim_count(s1, set);
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	j = 0;
	while (j < size)
	{
		dest[j] = s1[i + j];
		j++;
	}
	dest[size] = '\0';
	return (dest);
}
