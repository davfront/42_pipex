/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:13:46 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 11:10:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef PTR_NULL_PRINT
#  if __linux__
#   define PTR_NULL_PRINT "(nil)"
#  else
#   define PTR_NULL_PRINT "0x0"
#  endif
# endif

int		ft_print_c(unsigned char c);
int		ft_print_s(char *s);
int		ft_print_i(int i);
int		ft_print_u(unsigned int i);
int		ft_print_x(unsigned int i, int is_upper);
int		ft_print_p(unsigned long int p);
int		ft_printf(const char *s, ...);

#endif