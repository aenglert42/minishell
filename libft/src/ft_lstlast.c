/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:17:54 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/29 12:31:32 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_slist	*ft_lstlast(t_slist *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
