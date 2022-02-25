/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.0_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:08:04 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/25 22:21:01 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-------- begin of t-list funcitons------------

void	ft_addto_lst(t_slist **lst, char *str)
{
	ft_lstadd_back(lst, ft_lstnew(str));
}
//-------- end of t-list funcitons------------

//string functions:
int	ft_strindexrev(const char *str, int c)
{
	int		index;
	char	*s1;

	index = ft_strlen(str);
	s1 = (char *)str;
	while (s1[index] != c && index > 0)
	{
		index--;
	}
	if (s1[index] == c)
		return (index);
	else
		return (-1);
}

int	ft_strindex(const char *str, int c)
{
	int		index;
	char	*s1;

	index = 0;
	s1 = (char *)str;
	while (s1[index] != c && s1[index] != '\0')
	{
		index++;
	}
	if (s1[index] == c)
		return (index);
	else
		return (-1);
}
