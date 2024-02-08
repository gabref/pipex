/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:59:28 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/10 09:12:25 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dsize;
	size_t	i;

	dsize = 0;
	while (dsize < size && dst[dsize])
		dsize++;
	i = 0;
	while (src[i] && dsize + i + 1 < size)
	{
		dst[dsize + i] = src[i];
		i++;
	}
	if (dsize < size)
		dst[dsize + i] = '\0';
	return (dsize + ft_strlen(src));
}
