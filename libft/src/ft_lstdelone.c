/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:17:54 by aenglert          #+#    #+#             */
/*   Updated: 2021/12/19 10:19:16 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_slist *lst, void (*del)(void *))
{
	del(lst->content);
	lst->content = NULL;
	lst->next = NULL;
	free(lst);
}
