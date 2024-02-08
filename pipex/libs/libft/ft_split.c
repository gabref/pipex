/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:56:39 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/10 09:55:29 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (*str && str[i++] != c)
		words++;
	while (str[i])
	{
		if (str[i] && str[i] != c && str[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static void	fill(const char *s, char c, char **splitted, int words)
{
	int	start;
	int	end;
	int	c_word;

	c_word = 0;
	start = 0;
	end = 0;
	while (c_word < words)
	{
		start = end;
		while (s[start] && s[start] == c)
			start++;
		end = start + 1;
		while (s[end] && s[end] != c)
			end++;
		splitted[c_word++] = ft_substr((const char *)s, start, end - start);
	}
	*(splitted + c_word) = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**splitted;

	if (s == NULL)
		return (NULL);
	words = count_words((char *)s, c);
	splitted = (char **)malloc(sizeof(char *) * (words + 1));
	if (splitted == NULL)
		return (NULL);
	fill(s, c, splitted, words);
	return (splitted);
}
