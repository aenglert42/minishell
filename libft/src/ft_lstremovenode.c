/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremovenode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:11:54 by aenglert          #+#    #+#             */
/*   Updated: 2022/01/23 22:02:23 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremovenode(t_slist **lst, t_slist *node_to_remove,
	void (*del)(void *))
{
	t_slist	*tmp;

	tmp = *lst;
	if (tmp == NULL || node_to_remove == NULL)
		return ;
	if (tmp == node_to_remove)
	{
		*lst = tmp->next;
		del(node_to_remove->content);
		node_to_remove->content = NULL;
		free(node_to_remove);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == node_to_remove)
		{
			tmp->next = node_to_remove->next;
			del(node_to_remove->content);
			node_to_remove->content = NULL;
			free(node_to_remove);
			return ;
		}
		tmp = tmp->next;
	}
}
