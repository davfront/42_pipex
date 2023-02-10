/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:09 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/14 11:37:01 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_streq(const char *s1, const char *s2)
{
	if (s1 == NULL)
		return (s2 == NULL);
	return (ft_strncmp(s1, s2, ft_strlen(s1) + 1) == 0);
}
