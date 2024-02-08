/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:18:35 by galves-f          #+#    #+#             */
/*   Updated: 2023/11/04 01:27:38 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		size;
	int		i;

	size = ft_strlen(s);
	newstr = (char *)malloc(sizeof(char) * (size + 1));
	if (newstr == NULL)
		return (0);
	i = 0;
	while (*s)
		newstr[i++] = *s++;
	newstr[i] = '\0';
	return (newstr);
}
