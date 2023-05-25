/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:08:57 by isalhi            #+#    #+#             */
/*   Updated: 2022/10/18 20:06:03 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		error_exit("2ishell");
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
