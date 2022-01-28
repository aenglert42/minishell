/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.0_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/01/29 00:20:43 by englot           ###   ########.fr       */
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
	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		ft_exit_errno(data);
	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		array[i] = ft_strdup(tmp->content);
		if (array[i] == NULL)
			ft_exit_errno(data);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	ft_lstclear(tokens, &ft_del);
	return (array);
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

//assumption: str contains only closed quotes
char	**ft_tokenizer(char *str, t_data *data)
{
	t_slist *tokens;

	if (static_ft_has_unclosed_quotes(str, data))
		return (NULL);
	tokens = NULL;
	tokenize(str, data, &tokens);
	if (ft_clean_tokens(&tokens, data))
		return (NULL);
	if (static_ft_check_syntax_errors(&tokens, data))
		return (NULL);
	return (static_ft_create_command_array(&tokens, data));
}
