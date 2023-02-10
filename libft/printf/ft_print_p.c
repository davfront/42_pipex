/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa(.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 01:30:47 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/20 22:56:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_lx(unsigned long int p)
{
	int		len;

	if (p == 0)
		return (ft_print_c('0'));
	len = 0;
	if (p >= 16)
	{
		len = ft_print_lx(p / 16);
		if (len < 0)
			return (-1);
		p = p % 16;
	}
	if (ft_print_c(("0123456789abcdef")[p]) < 0)
		return (-1);
	return (len + 1);
}

int	ft_print_p(unsigned long int p)
{
	int	len;

	if (!p)
		return (ft_print_s(PTR_NULL_PRINT));
	if (ft_print_s("0x") < 0)
		return (-1);
	len = ft_print_lx(p);
	if (len < 0)
		return (-1);
	return (2 + len);
}
