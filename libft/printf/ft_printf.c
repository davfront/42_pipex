/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:32:46 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 11:17:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_type(char type)
{
	return (ft_strchr("csdiupxX%", type) != NULL);
}

static int	print_arg(va_list args, char type)
{
	if (type == 'c')
		return (ft_print_c((unsigned char)va_arg(args, int)));
	if (type == 's')
		return (ft_print_s((char *)va_arg(args, const char *)));
	if (type == 'd' || type == 'i')
		return (ft_print_i(va_arg(args, int)));
	if (type == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	if (type == 'p')
		return (ft_print_p((unsigned long int)va_arg(args, void *)));
	if (type == 'x')
		return (ft_print_x(va_arg(args, unsigned int), 0));
	if (type == 'X')
		return (ft_print_x(va_arg(args, unsigned int), 1));
	if (type == '%')
		return (ft_print_c('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		len;
	int		count;

	if (!s || !(*s))
		return (0);
	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1) && is_type(*(s + 1)))
		{
			len = print_arg(args, *(s + 1));
			s++;
		}
		else
			len = ft_print_c(*s);
		s++;
		if (len < 0)
			return (-1);
		count += len;
	}
	va_end(args);
	return (count);
}
