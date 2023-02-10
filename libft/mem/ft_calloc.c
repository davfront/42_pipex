/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:45:45 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 11:15:07 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	malloc_size;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	malloc_size = nmemb * size;
	ptr = (void *)malloc(malloc_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, malloc_size);
	return (ptr);
}
