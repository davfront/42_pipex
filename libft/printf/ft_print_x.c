/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 01:30:47 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 11:17:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_x(unsigned int x, int is_upper)
{
	int		len;
	char	c;

	if (x == 0)
		return (ft_print_c('0'));
	len = 0;
	if (x >= 16)
	{
		len = ft_print_x(x / 16, is_upper);
		if (len < 0)
			return (-1);
		x = x % 16;
	}
	c = ("0123456789abcdef")[x];
	if (is_upper)
		c = ("0123456789ABCDEF")[x];
	if (ft_print_c(c) < 0)
		return (-1);
	return (len + 1);
}
