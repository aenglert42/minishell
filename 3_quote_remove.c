/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_quote_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:23:32 by jzhou             #+#    #+#             */
/*   Updated: 2022/01/27 21:46:23 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_remove_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i + 2] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

void		ft_quoteremover(char **command)
{
	int	i;

	i = 0;
	while (command[i] != NULL)
	{
		if (command[i][0] == '\'' || command[i][0] == '\"')
			static_remove_quotes(command[i]);
		i++;
	}
}