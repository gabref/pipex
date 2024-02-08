/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:29:34 by galves-f          #+#    #+#             */
/*   Updated: 2023/11/05 16:31:42 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(long n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		digits++;
	}
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*nstr;
	int		len;
	long	ln;

	ln = (long)n;
	len = get_digits(ln);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (nstr == NULL)
		return (NULL);
	if (ln == 0)
		nstr[0] = '0';
	if (ln < 0)
	{
		ln *= -1;
		nstr[0] = '-';
	}
	nstr[len] = '\0';
	while (ln)
	{
		nstr[--len] = ln % 10 + 48;
		ln /= 10;
	}
	return (nstr);
}
