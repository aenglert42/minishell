/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:17:54 by aenglert          #+#    #+#             */
/*   Updated: 2021/12/19 10:21:15 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_slist **lst, void (*del)(void *))
{
	t_slist	*tmp;
	t_slist	*next;

	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		next = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = next;
	}
	*lst = NULL;
}
