/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_tokenizer_fth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/22 12:05:24 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function checks for complete single quotes
bool	ft_checksingle(char *input, int *i)
{
	while (input[*i] != '\0' && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
		(*i)++;
	else if (input[*i] == '\0')
		return (false);
	return (true);
}

//this function checks for complete double quotes
bool	ft_checkdouble(char *input, int *i)
{
	while (input[*i] != '\0' && input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
		(*i)++;
	else if (input[*i] == '\0')
		return (false);
	return (true);
}

//this function checks if the quotes are ok
char	*ft_checkquotes(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			i++;
			if (ft_checksingle(input, &i) == false)
				return (ft_quoteerror(data));
		}
		else if (input[i] == '"')
		{
			i++;
			if (ft_checkdouble(input, &i) == false)
				return (ft_quoteerror(data));
		}
		else
			i++;
	}
	return (input);
}

//this function merges all successive redirections together 
void	ft_mergeall(char **command, char **finalcmd, int *y, int *mcounter)
{
	while (command[*y] != NULL && (command[*y][0] == '>'
		|| command[*y][0] == '<'))
	{
		finalcmd[*mcounter] = ft_strjoin(finalcmd[*mcounter],
				command[*y]);
		(*y)++;
	}
	(*mcounter)++;
}
