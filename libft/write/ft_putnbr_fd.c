/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:37:16 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/14 03:09:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n2;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n2 = -n;
	}
	else
		n2 = n;
	if (n2 > 9)
	{
		ft_putnbr_fd(n2 / 10, fd);
		n2 = n2 % 10;
	}
	ft_putchar_fd(n2 + '0', fd);
}
