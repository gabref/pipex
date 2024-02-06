/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:55:47 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/06 14:56:48 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*get_next_word(char *str, char sep)
{
	static unsigned long	cursor = 0;
	char					*nstr;
	int						len;
	int						i;

	len = 0;
	while (str[cursor] && str[cursor] == sep)
		cursor++;
	while (str[cursor + len] && str[cursor + len] != sep)
		len++;
	nstr = malloc(sizeof(char) * (len + 1));
	if (nstr == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		nstr[i] = str[cursor + i];
	nstr[i] = '\0';
	cursor += len;
	return (nstr);
}

int	count_words(char *str, char sep)
{
	int	words;
	int	is_start;

	words = 0;
	while (*str)
	{
		is_start = 0;
		while (*str && *str == sep)
			str++;
		while (*str && *str != sep)
		{
			if (!is_start)
			{
				is_start = 1;
				words++;
			}
			str++;
		}
	}
	return (words);
}

char	**split(char *str, char sep)
{
	int		words;
	char	**splitted;
	int		i;

	words = count_words(str, sep);
	if (!words)
		exit(1);
	splitted = malloc(sizeof(char *) * (words + 2));
	if (splitted == NULL)
		return (NULL);
	i = 0;
	splitted[i++] = NULL;
	while (i < words + 1)
		splitted[i++] = get_next_word(str, sep);
	splitted[i] = NULL;
	return (splitted);
}
