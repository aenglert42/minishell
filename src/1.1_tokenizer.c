/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:54:28 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	static_ft_handle_bigger(t_slist **tokens,
				t_data *data, t_slist **ptr)
{
	if ((*ptr)->next == NULL || ft_strcmp((*ptr)->next->content, "<"))
		return (ft_exit_tokenizer(data, tokens));
	if (ft_strcmp((*ptr)->next->content, ">"))
	{
		if (ft_strappend2(((char **)&(*ptr)->content), ">"))
			return (EXIT_FAILURE);
		ft_lstremovenode(tokens, (*ptr)->next, &ft_del);
	}
	*ptr = (*ptr)->next;
	return (EXIT_SUCCESS);
}

static int	static_ft_handle_smaller(t_slist **tokens,
				t_data *data, t_slist **ptr)
{
	if ((*ptr)->next == NULL || ft_strcmp((*ptr)->next->content, ">"))
		return (ft_exit_tokenizer(data, tokens));
	if (ft_strcmp((*ptr)->next->content, "<"))
	{
		if (ft_strappend2((char **)&(*ptr)->content, "<"))
			return (EXIT_FAILURE);
		ft_lstremovenode(tokens, (*ptr)->next, &ft_del);
	}
	*ptr = (*ptr)->next;
	return (EXIT_SUCCESS);
}

static int	static_ft_handle_redirection(t_slist **tokens,
				t_data *data, t_slist **ptr)
{
	if (ft_strcmp((*ptr)->content, "<"))
	{
		if (static_ft_handle_smaller(tokens, data, ptr))
			return (EXIT_FAILURE);
	}
	else
	{
		if (static_ft_handle_bigger(tokens, data, ptr))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_clean_tokens(t_slist **tokens, t_data *data)
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
		else if (ft_strcmp(ptr->content, "<") || ft_strcmp(ptr->content, ">"))
		{
			if (static_ft_handle_redirection(tokens, data, &ptr))
				return (EXIT_FAILURE);
		}
		else
			ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
