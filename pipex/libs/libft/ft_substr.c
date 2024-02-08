/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:17:45 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/11 15:56:44 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	int		size_substring;
	int		original_size;

	if (s == NULL)
		return (NULL);
	original_size = ft_strlen(s);
	if (start >= (unsigned int)original_size)
		return (ft_strdup(""));
	size_substring = original_size - start;
	if (len > (unsigned int)size_substring)
		len = size_substring;
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s + start, len + 1);
	return (newstr);
}
