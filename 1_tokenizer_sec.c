/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_tokenizer_sec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/22 21:23:04 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//in this file you can find the main tokenizer-function

//this function scans for the second corresponding quote
//and returns true or false
int	ft_finddouble(int i, char *input)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == '"')
			break ;
		else
			i++;
	}
	i++;
	return (i);
}

//this function scans for the second corresponding quote
//and returns true or false
int	ft_findsingle(int i, char *input)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			break ;
		else
			i++;
	}
	i++;
	return (i);
}

//second step: contains all the functions to create the char **command
char	**ft_createcmd(t_slist *tokenlst)
{
	int		node;
	int		y;
	char	**command;

	node = ft_lstsize(tokenlst);
	y = 0;
	command = malloc((node + 1) * sizeof(char *));
	if (command == NULL)
		return (NULL);
	while (y < node)
	{
		command[y] = ft_strdup((char *)(tokenlst->content));
		tokenlst = tokenlst->next;
		y++;
	}
	command[y] = NULL;
	return (command);
}

//this function frees all allocated unneeded stuff
void	ft_freetokenizer(char **command, char **temp)
{
	freedchar(&command);
	freedchar(&temp);
}

//this is the main tokenizer function
char	**ft_tokenizer(char *input, t_data *data)
{
	t_slist	*tokenlst;
	char	**command;
	char	**temp;
	char	**temp2;

	command = NULL;
	tokenlst = ft_firstrun(input, data);
	if (tokenlst != NULL)
	{
		if (ft_triple_re(tokenlst, data))
			return (NULL);
		command = ft_createcmd(tokenlst);
		ft_lstclear(&tokenlst, ft_del);
		temp = ft_merge_redirect(command, data);
		if (temp == NULL)
			return (NULL);
		temp2 = ft_allocnospace(temp);
		ft_erasespace(temp, temp2);
		ft_freetokenizer(command, temp);
		return (temp2);
	}
	return (NULL);
}
