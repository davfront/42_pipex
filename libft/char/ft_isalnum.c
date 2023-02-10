/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:22:35 by dapereir          #+#    #+#             */
/*   Updated: 2022/11/16 13:57:47 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	int	isalpha;
	int	isnumeric;

	isalpha = ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
	isnumeric = (c >= '0' && c <= '9');
	return (isalpha || isnumeric);
}
