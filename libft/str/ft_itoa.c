/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 01:30:47 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/21 09:24:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_itoa(int n)
{
	size_t			len;
	unsigned int	n2;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n2 = -n;
	}
	else
		n2 = n;
	while (n2 > 0)
	{
		n2 = n2 / 10;
		len++;
	}
	return (len);
}

static void	set_itoa(char *str, size_t len, int n)
{
	unsigned int	n2;
	unsigned int	i;

	n2 = 0;
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		n2 = -n;
	}
	else
		n2 = n;
	i = len - 1;
	while (n2 > 0)
	{
		str[i] = (n2 % 10) + '0';
		n2 = n2 / 10;
		i--;
	}
	str[len] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = count_itoa(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	set_itoa(str, len, n);
	return (str);
}
