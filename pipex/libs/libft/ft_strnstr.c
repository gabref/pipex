/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:19:42 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/10 09:12:40 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	k;

	j = 0;
	if (!*needle || (NULL == haystack && !len))
		return ((char *)haystack);
	while (*(haystack + j) && j < len)
	{
		k = 0;
		while (*(haystack + j + k) == *(needle + k) && (k + j) < len)
		{
			if (0 == *(needle + k + 1))
				return ((char *)haystack + j);
			++k;
		}
		++j;
	}
	return (NULL);
}

/*
static int	is_word(const char *str, const char *word)
{
	if (!*word && !*str)
		return (1);
	while (*word)
		if (*word++ != *str++)
			return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	nsize;
	int	search_until;

	if (!*needle || (haystack == NULL && !len))
		return ((char *)haystack);
	nsize = ft_strlen(needle);
	search_until = len - nsize;
	while (search_until-- >= 0 && *haystack)
		if (is_word(haystack++, needle))
			return ((char *)--haystack);
	return (NULL);
}
*/
