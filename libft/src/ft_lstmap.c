/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:30:37 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/29 12:31:32 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_slist	*ft_lstmap(t_slist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_slist	*new;
	t_slist	*tmp;

	new = 0;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
			ft_lstclear(&new, del);
		else
			ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}
