/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:08:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/11 15:54:53 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newn)
{
	t_list	*current;

	if (!lst)
		return ;
	current = *lst;
	if (current == NULL)
	{
		*lst = newn;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = newn;
}
