/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_quote_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:54:42 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	static_remove_quotes(char *str, int j)
{
	int		i;
	char	quote;

	quote = str[j];
	while (str[j + 1] != quote)
	{
		str[j] = str[j + 1];
		j++;
	}
	i = 0;
	while (str[j + 2 + i] != '\0')
	{
		str[j + i] = str[j + 2 + i];
		i++;
	}
	str[j + i] = '\0';
	return (j);
}

void	ft_quoteremover(char **command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i] != NULL)
	{
		j = 0;
		while (command[i][j] != '\0')
		{
			if (command[i][j] == '\'' || command[i][j] == '\"')
				j = static_remove_quotes(command[i], j);
			else
				j++;
		}
		i++;
	}
}
