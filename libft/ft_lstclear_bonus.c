/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 01:10:46 by isalhi            #+#    #+#             */
/*   Updated: 2022/11/12 15:19:30 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;
	t_list	*to_del;

	if (!lst)
		return ;
	head = *lst;
	while (head)
	{
		to_del = head;
		head = head->next;
		ft_lstdelone(to_del, del);
	}
	*lst = NULL;
}
