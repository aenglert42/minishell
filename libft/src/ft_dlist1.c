/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:11:54 by aenglert          #+#    #+#             */
/*   Updated: 2022/02/21 20:51:58 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *node_to_add)
{
	node_to_add->next = *lst;
	if (*lst)
		(*lst)->prev = node_to_add;
	*lst = node_to_add;
	node_to_add->prev = NULL;
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *node_to_add)
{
	t_dlist	*last;

	if (*lst == NULL)
	{
		*lst = node_to_add;
		return ;
	}
	last = ft_dlstlast(*lst);
	last->next = node_to_add;
	node_to_add->prev = last;
	node_to_add->next = NULL;
}

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*new_node;

	new_node = malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
