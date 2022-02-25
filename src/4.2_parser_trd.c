/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.2_parser_trd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/25 22:20:38 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function counts up the number of arguments for mallocing char **args
int	ft_countargs(char **command, t_data *data, int y, int argscount)
{
	while (command[y] != NULL)
	{
		if (ft_strcmp_n("\x1d", command[y], 2) == 0
			|| ft_strcmp_n("\x1d\x1d", command[y], 3) == 0
			|| ft_strcmp_n("\x1c", command[y], 2) == 0
			|| ft_strcmp_n("\x1c\x1c", command[y], 3) == 0)
		{
			y++;
			if (command[y] == NULL)
			{
				ft_syntaxerr(data);
				return (10000);
			}
		}
		else
		{
			argscount++;
			y++;
		}
	}
	return (argscount);
}

//this function initializes the simplecmd struct
int	ft_initsimple(t_cmd *simplecmd, char **command, t_data *data)
{
	int	argscount;

	argscount = ft_countargs(command, data, 0, 0) + 1;
	if (argscount >= 10000)
		return (-1);
	simplecmd->path = NULL;
	simplecmd->args = (char **)malloc(argscount * sizeof(char *));
	if (simplecmd->args == NULL)
		return (-1);
	simplecmd->hasheredoc = false;
	simplecmd->isbuiltin = false;
	simplecmd->re = NULL;
	simplecmd->pid = 0;
	simplecmd->fd[0] = 0;
	simplecmd->fd[1] = 1;
	return (0);
}

// here we check for built-ins.
bool	ft_checkbuiltin(char *commandpart)
{
	if (ft_strcmp_n(commandpart, "echo", 5) == 0)
		return (true);
	if (ft_strcmp_n(commandpart, "cd", 3) == 0)
		return (true);
	if (ft_strcmp_n(commandpart, "pwd", 4) == 0)
		return (true);
	if (ft_strcmp_n(commandpart, "export", 7) == 0)
		return (true);
	if (ft_strcmp_n(commandpart, "unset", 6) == 0)
		return (true);
	if (ft_strcmp_n(commandpart, "env", 4) == 0)
		return (true);
	if (ft_strcmp_n(commandpart, "exit", 5) == 0)
		return (true);
	return (false);
}

void	builtinflag(t_cmd *simplecmd)
{
	if (simplecmd->args[0] == NULL)
	{
		simplecmd->isbuiltin = false;
		return ;
	}
	if (ft_checkbuiltin(simplecmd->args[0]) == true)
		simplecmd->isbuiltin = true;
}

int	ft_splithelper(char **newstr, t_slist **cmdtable, t_data *data)
{
	t_cmd	*simplecmd;

	simplecmd = malloc(sizeof(*simplecmd));
	if (ft_initsimple(simplecmd, newstr, data) == -1)
		return (10000);
	if (ft_sortcmdret(newstr, simplecmd, data) == -1)
		return (10000);
	freedchar(&newstr);
	newstr = NULL;
	ft_lstadd_back(cmdtable, ft_lstnew(simplecmd));
	return (0);
}
