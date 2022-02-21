/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.1_parser_sec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/21 21:32:30 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//here is the main part of making sense of the commands and
//storing them into the command table

//this function fills up the t_cmd simplecmd struct
int	ft_sort_cmd(char **command, t_cmd *simplecmd, int y, t_data *data)
{
	int		x;
	bool	isfirsttime;

	x = 0;
	isfirsttime = true;
	while (command[y] != NULL)
	{
		if (ft_isredirection(command, &y) == false)
		{	
			if (isfirsttime == true)
			{
				isfirsttime = false;
				ft_cmdargs(command, simplecmd, &x, &y);
			}
			else
				ft_fillargs(simplecmd, command, &x, &y);
		}
		else
		{
			if (ft_distinguish(command, &y, simplecmd, data) == -1)
				return (-1);
		}		
	}
	simplecmd->args[x] = NULL;
	return (0);
}

int	ft_sortcmdret(char **command, t_cmd *simplecmd, t_data *data)
{
	if (ft_sort_cmd(command, simplecmd, 0, data) == -1)
		return (-1);
	builtinflag(simplecmd);
	return (0);
}

//this function creates the simple commands divided by '|'
int	ft_splitdptr(char **command, t_slist **cmdtable, t_data *data)
{
	int		cmdcount;
	int		seccount;
	char	**newstr;

	cmdcount = 0;
	while (command[cmdcount] != NULL)
		cmdcount++;
	newstr = (char **)malloc((cmdcount + 1) * sizeof(char *));
	seccount = 0;
	while (seccount < cmdcount)
	{
		newstr[seccount] = ft_strdup(command[seccount]);
		seccount++;
	}
	newstr[seccount] = NULL;
	if (ft_splithelper(newstr, cmdtable, data) >= 10000)
		return (10000);
	cmdcount++;
	return (cmdcount);
}

//this function replaces '|' with PIPE
char	**dividecmd(char **command, char **newcmd, int cmdcount)
{
	int		current;

	current = 0;
	while (current < cmdcount)
	{
		if (command[current][0] == PIPE)
			newcmd[current] = NULL;
		else
			newcmd[current] = ft_strdup(command[current]);
		current++;
	}
	newcmd[current] = NULL;
	return (newcmd);
}

//this is the main parser function and create the cmdtable-list
//1. count the char **command
//2. replace '|' with PIPE function
//3. parse the char ** to the node-creator
t_slist	*ft_parser(char **command, t_data *data)
{
	int		cmdcount;
	int		pipecount;
	char	**newcmd;
	t_slist	*cmdtable;

	cmdcount = 0;
	pipecount = 0;
	newcmd = NULL;
	cmdtable = NULL;
	while (command[cmdcount] != NULL)
		cmdcount++;
	newcmd = (char **)malloc((cmdcount + 1) * sizeof(char *));
	newcmd = dividecmd(command, newcmd, cmdcount);
	freedchar(&command);
	command = NULL;
	while (pipecount < cmdcount)
		pipecount += ft_splitdptr(newcmd + pipecount, &cmdtable, data);
	parser_freedchar(&newcmd, cmdcount);
	if (pipecount > 10000)
	{
		ft_freepipecount(command, newcmd, cmdtable);
		return (NULL);
	}
	return (cmdtable);
}
