/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.2_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:08:04 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/25 22:21:07 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-------- begin of t-re funcitons------------
void	ft_del(void *content)
{
	free(content);
}

void	ft_delre(char *file)
{
	free (file);
}

void	ft_relstdelone(t_re *re, void (*del)(void *))
{
	if (re == NULL || del == 0)
		return ;
	re->operator = 0;
	(*ft_delre)(re->file);
	free(re);
}
