/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/01/24 00:06:56 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**static_ft_create_command_array(t_slist *tokens)
{
	int		count;
	char	**array;
	t_slist	*tmp;
	int		i;

	count = ft_lstsize(tokens);
	array = malloc((count + 1) * sizeof(char *)); //malloccheck
	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		array[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

static void	static_ft_clean_tokens(t_slist **tokens) //check triple <
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
				printf("error |\n"); //errorcheck multiple |s
			((char *)ptr->content)[0] = PIPE;
		}
		else if (ft_strcmp(ptr->content, "<"))
		{
			if (ptr->next == NULL)
				printf("error <\n"); //errorcheck
			if (ft_strcmp(ptr->next->content, "<"))
			{
			ft_strappend2(((char **)&ptr->content), "<");
			ft_lstremovenode(tokens, ptr->next, &ft_del);
			}
			ptr = ptr->next;
		}
		else if (ft_strcmp(ptr->content, ">"))
		{
			if (ptr->next == NULL)
				printf("error >\n"); //errorcheck
			if (ft_strcmp(ptr->next->content, ">"))
			{
			ft_strappend2(((char **)&ptr->content), ">");
			ft_lstremovenode(tokens, ptr->next, &ft_del);
			}
			ptr = ptr->next;
		}
		else
			ptr = ptr->next;
	}
	ptr = *tokens;
	while (ptr != NULL)
	{
		printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
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

char	**ft_tokenizer(char *str) //gets adress of linked list
{
	//assumption: str contains only closed quotes
	int		i;
	int		pos;
	char	*tmp;
	t_slist *tokens;
	t_slist	*node;
	
	tokens = NULL;
	i = 0;
	pos = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (i > pos)
			{
				tmp = ft_substr(str, pos, i - pos);
				node = ft_lstnew(tmp);
				ft_lstadd_back(&tokens, node);
				printf("1[%d]: %s.\n", i, tmp);
				pos = i;
			}
			i += static_ft_step_through_quote(str + i, str[i]);
			tmp = ft_substr(str, pos, i - pos);
			node = ft_lstnew(tmp);
			ft_lstadd_back(&tokens, node);
			printf("2[%d]: %s.\n", i, tmp);
			pos = i;
		}
		else if (str[i] == ' '|| str[i] == '\t' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (i > pos)
			{
				tmp = ft_substr(str, pos, i - pos);
				node = ft_lstnew(tmp);
				ft_lstadd_back(&tokens, node);
				printf("3[%d]: %s.\n", i, tmp);
				pos = i;
			}
			i++;
			tmp = ft_substr(str, pos, i - pos);
			node = ft_lstnew(tmp);
			ft_lstadd_back(&tokens, node);
			printf("4[%d]: %s.\n", i, tmp);
			pos = i;
		}
		else
			i++;
	}
	if (i > pos)
	{
		tmp = ft_substr(str, pos, i - pos);
		node = ft_lstnew(tmp);
		ft_lstadd_back(&tokens, node);
		printf("5[%d]: %s.\n", i, tmp);
	}
	static_ft_clean_tokens(&tokens);
	return (static_ft_create_command_array(tokens));
}
