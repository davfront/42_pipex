/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:57:36 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 11:17:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_i(int i)
{
	unsigned int	u;
	int				is_negative;
	int				u_len;

	is_negative = 0;
	if (i < 0)
	{
		if (ft_print_c('-') < 0)
			return (-1);
		is_negative = 1;
		u = -i;
	}
	else
		u = i;
	u_len = ft_print_u(u);
	if (u_len < 0)
		return (-1);
	return (is_negative + u_len);
}
