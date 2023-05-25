/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 01:34:46 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/18 20:05:40 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		elem = ft_lstnew(lst->content);
		if (!elem)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		elem->content = f(elem->content);
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
