/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.3_parser_fth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function fills the arguments of the commands (if its the firsttime)
void	ft_args(t_cmd *simplecmd, char **command, int *x, int *y)
{
	int	index;

	index = 0;
	simplecmd->path = ft_strdup(command[*y]);
	index = ft_strindexrev(command[*y], '/') + 1;
	simplecmd->args[*x] = ft_substr(command[*y], index,
			(ft_strlen(command[*y]) - index));
	(*y)++;
	(*x)++;
}

//this function fills the path and command part of the struct
//simplecmd (if its the firsttime)
void	ft_pathcmd(t_cmd *simplecmd, char **command, int *x, int *y)
{
	simplecmd->path = ft_strdup(command[*y]);
	simplecmd->args[*x] = ft_strdup(command[*y]);
	(*y)++;
	(*x)++;
}

//this function fills up the main command in the simplecmd-struct
void	ft_cmdargs(char **command, t_cmd *simplecmd, int *x, int *y)
{
	if (ft_strindex(command[*y], '/') != -1)
		ft_args(simplecmd, command, x, y);
	else
		ft_pathcmd(simplecmd, command, x, y);
}

//this function fills up all the sucsessive arguments (isfirsttime == false)
void	ft_fillargs(t_cmd *simplecmd, char **command, int *x, int *y)
{
	simplecmd->args[*x] = ft_strdup(command[*y]);
	(*y)++;
	(*x)++;
}

//this function checks if the cmdtable is empty
bool	ft_emptystruct(t_slist *cmdtable, t_data *data)
{
	t_slist	*temp;

	temp = cmdtable;
	if (temp == NULL)
		return (true);
	while (temp != NULL)
	{
		if (((t_cmd *)temp->content)->path == NULL
			&& ((t_cmd *)temp->content)->args[0] == NULL
			&& ((t_cmd *)temp->content)->re == NULL)
			return (ft_syntaxcheck(data));
		temp = temp->next;
	}
	return (false);
}
