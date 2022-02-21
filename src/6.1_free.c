/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.1_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:24:45 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_ft_del(void *content)
{
	int		i;
	t_cmd	*cmd;
	t_re	*re;

	cmd = ((t_cmd *)content);
	free(cmd->path);
	i = 0;
	while (cmd->args != NULL && cmd->args[i] != NULL)
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
	re = cmd->re;
	ft_relstclear(&re, ft_del);
	free(content);
}

void	ft_free_commandlist(t_slist **commands)
{
	if (commands == NULL)
		return ;
	ft_lstclear(commands, static_ft_del);
	return ;
}

void	freedchar(char ***dchar)
{
	int	i;

	if (*dchar == NULL)
		return ;
	i = 0;
	while ((*dchar)[i] != NULL)
	{
		free((*dchar)[i]);
		(*dchar)[i] = NULL;
		i++;
	}
	free(*dchar);
	*dchar = NULL;
}

void	ft_free_data_struct_content(t_data *data)
{
	if (data == NULL)
		return ;
	freedchar(&data->myenv);
	ft_free_commandlist(&data->commands);
}

void	parser_freedchar(char ***dchar, int count)
{
	int	i;

	if (*dchar == NULL)
		return ;
	i = 0;
	while (i <= count)
	{
		free((*dchar)[i]);
		(*dchar)[i] = NULL;
		i++;
	}
	free(*dchar);
	*dchar = NULL;
}
