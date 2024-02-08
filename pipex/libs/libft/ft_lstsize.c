/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:04:08 by galves-f          #+#    #+#             */
/*   Updated: 2023/11/06 00:23:31 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	nodes;

	nodes = 0;
	if (!lst)
		return (0);
	while (lst->next)
	{
		nodes++;
		lst = lst->next;
	}
	nodes++;
	return (nodes);
}
