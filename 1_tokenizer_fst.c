/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_tokenizer_fst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/21 23:39:08 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//first step: count tokens and allocate char **command
//this function scans for single metacharacters
bool	ft_scanmeta(char c1)
{
	if (c1 == '|' || c1 == '<' || c1 == '>' || c1 == ' ')
		return (true);
	return (false);
}

//this function splits the meta-characters ( space, <, >, |)
int	ft_filtermeta(int i, char *input, int start, t_slist **tokenlst)
{
	char	*token;

	if (i > start)
	{
		token = ft_substr(input, start, i - start);
		ft_addto_lst(tokenlst, token);
	}
	token = ft_substr(input, i, 1);
	ft_addto_lst(tokenlst, token);
	i++;
	return (i);
}

//this function frees and returns the tokenlst upon error
t_slist	*errortokenlst(t_slist *tokenlst)
{
	ft_lstclear(&tokenlst, ft_del);
	return (tokenlst);
}

//this function loops through and checks if there are quotes missing,
//as well as add tokens to the tokenlst
t_slist	*scantokenlst(int *i, int *start, char *input, t_slist *tokenlst)
{
	while (input[*i] != '\0')
	{
		if (input[*i] == '"')
			*i = ft_finddouble(*i, input);
		else if (input[*i] == '\'')
			*i = ft_findsingle(*i, input);
		else if (ft_scanmeta(input[*i]) == true)
		{
			*i = ft_filtermeta(*i, input, *start, &tokenlst);
			*start = *i;
		}
		else
			(*i)++;
	}
	return (tokenlst);
}

//this funciton scans for quotes or meta characters
t_slist	*ft_firstrun(char *input, t_data *data)
{
	t_slist	*tokenlst;
	int		i;
	int		start;
	char	*token;

	i = 0;
	start = 0;
	tokenlst = NULL;
	token = NULL;
	if (ft_checkquotes(input, data) == NULL)
		return (tokenlst);
	tokenlst = scantokenlst(&i, &start, input, tokenlst);
	if (input[i] == '\0')
	{
		if (i - start > 0)
		{
			token = ft_substr(input, start, i - start);
			ft_addto_lst(&tokenlst, token);
		}
	}
	return (tokenlst);
}
