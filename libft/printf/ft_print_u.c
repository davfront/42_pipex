/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 01:30:47 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 11:17:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_u(unsigned int u)
{
	int		len;

	if (u == 0)
		return (ft_print_c('0'));
	len = 0;
	if (u >= 10)
	{
		len = ft_print_u(u / 10);
		if (len < 0)
			return (-1);
		u = u % 10;
	}
	if (ft_print_c(u + '0') < 0)
		return (-1);
	return (len + 1);
}
