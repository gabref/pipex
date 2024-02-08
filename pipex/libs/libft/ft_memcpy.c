/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:13:36 by galves-f          #+#    #+#             */
/*   Updated: 2023/11/01 23:37:46 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d_buffer;
	unsigned char	*s_buffer;

	d_buffer = (unsigned char *)dest;
	s_buffer = (unsigned char *)src;
	if (!d_buffer && !s_buffer)
		return (NULL);
	while (n--)
		*(d_buffer + n) = *(s_buffer + n);
	return ((void *)d_buffer);
}
