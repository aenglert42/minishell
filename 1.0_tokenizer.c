/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.0_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/01/27 22:38:32 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	static_ft_check_syntax_errors(t_slist **tokens, t_data *data)
{
	t_slist	*ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->content, "<<"))
		{
			if (ptr->next == NULL || ft_strcmp(ptr->next->content, "<") || ft_strcmp(ptr->next->content, ">"))
				return (ft_exit_tokenizer(data, tokens));
		}
		if (ft_strcmp(ptr->content, ">>"))
		{
			if (ptr->next == NULL || ft_strcmp(ptr->next->content, "<") || ft_strcmp(ptr->next->content, ">"))
				return (ft_exit_tokenizer(data, tokens));
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

static char	**static_ft_create_command_array(t_slist **tokens, t_data *data)
{
	int		count;
	char	**array;
	t_slist	*tmp;
	int		i;

	count = ft_lstsize(*tokens);
	array = malloc((count + 1) * sizeof(char *)); //malloccheck
	if (array == NULL)
		ft_exit_errno(data);
	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		array[i] = ft_strdup(tmp->content); //malloccheck
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	ft_lstclear(tokens, &ft_del);
	ft_print_tokenarray(array); //remove
	return (array);
}

static int	static_ft_clean_tokens(t_slist **tokens, t_data *data) //check triple <
{
	t_slist	*ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->content, " "))
		{
			ft_lstremovenode(tokens, ptr, &ft_del);
			ptr = *tokens;
		}
		else if (ft_strcmp(ptr->content, "|"))
		{
			if (ptr->next == NULL || ft_strcmp(ptr->next->content, "|"))
				return (ft_exit_tokenizer(data, tokens));
			((char *)ptr->content)[0] = PIPE;
		}
		else if (ft_strcmp(ptr->content, "<"))
		{
			if (ptr->next == NULL || ft_strcmp(ptr->next->content, ">"))
				return (ft_exit_tokenizer(data, tokens));
			if (ft_strcmp(ptr->next->content, "<"))
			{
			ft_strappend2(((char **)&ptr->content), "<"); //malloccheck
			ft_lstremovenode(tokens, ptr->next, &ft_del);
			}
			ptr = ptr->next;
		}
		else if (ft_strcmp(ptr->content, ">"))
		{
			if (ptr->next == NULL || ft_strcmp(ptr->next->content, "<"))
				return (ft_exit_tokenizer(data, tokens));
			if (ft_strcmp(ptr->next->content, ">"))
			{
			ft_strappend2(((char **)&ptr->content), ">"); //malloccheck
			ft_lstremovenode(tokens, ptr->next, &ft_del);
			}
			ptr = ptr->next;
		}
		else
			ptr = ptr->next;
	}
	ft_print_tokenlist(tokens); //remove
	return (EXIT_SUCCESS);
}

static int static_ft_step_through_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0') ////unnecessary?
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}

static bool	static_ft_has_unclosed_quotes(char *str, t_data *data)
{
	int	i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] != '\0' && str[i] != quote)
				i++;
			if (str[i] == '\0')
			{
				data->lastexitstatus = SYNTAX;
				ft_printf_stderr("%s: Error: unclosed quotes\n", SHELL);
				return (true);
			}
		}
		i++;
	}
	return (false);
}

// static t_slist	**static_tokenize_quotes(t_slist **tokenlist, int *i, int *pos, char *str)
// {
// 	char	*tmp;
// 	t_slist	*node;
	
// 	if (*i > *pos)
// 	{
// 		tmp = ft_substr(str, *pos, *i - *pos);
// 		node = ft_lstnew(tmp); //malloccheck
// 		ft_lstadd_back(tokenlist, node);
// 		*pos = *i;
// 	}
// 	*i += static_ft_step_through_quote(str + *i, str[*i]);
// 	tmp = ft_substr(str, *pos, *i - *pos);
// 	node = ft_lstnew(tmp); //malloccheck
// 	ft_lstadd_back(tokenlist, node);
// 	*pos = *i;
// 	return (tokenlist);
// }

// static void	static_ft_create_token()
// {
	
// }

char	**ft_tokenizer(char *str, t_data *data)
{
	//assumption: str contains only closed quotes
	int		i;
	int		pos;
	char	*tmp;
	t_slist *tokens;
	t_slist	*node;

	if (static_ft_has_unclosed_quotes(str, data))
		return (NULL);
	tokens = NULL;
	i = 0;
	pos = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += static_ft_step_through_quote(str + i, str[i]);
//			static_tokenize_quotes(&tokens, &i, &pos, str); //NULLcheck
		}
		else if (str[i] == ' '|| str[i] == '\t' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (i > pos)
			{
				tmp = ft_substr(str, pos, i - pos);
				node = ft_lstnew(tmp); //malloccheck
				ft_lstadd_back(&tokens, node);
				pos = i;
			}
			i++;
			tmp = ft_substr(str, pos, i - pos);
			node = ft_lstnew(tmp); //malloccheck
			ft_lstadd_back(&tokens, node);
			pos = i;
		}
		else
			i++;
	}
	if (i > pos)
	{
		tmp = ft_substr(str, pos, i - pos);
		node = ft_lstnew(tmp); //malloccheck
		ft_lstadd_back(&tokens, node);
	}
	if (static_ft_clean_tokens(&tokens, data))
		return (NULL);
	if (static_ft_check_syntax_errors(&tokens, data))
		return (NULL);
	return (static_ft_create_command_array(&tokens, data));
}
