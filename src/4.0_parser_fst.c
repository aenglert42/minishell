/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.0_parser_fst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/25 22:20:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this file stores most of the redirections-handling

//this function checks if it is a heredoc or a simple in-redirection
int	ft_inredirect(char **command, int *y, t_cmd *simplecmd, t_data *data)
{
	if (ft_strcmp_n("\x1d\x1d", command[*y], 3) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(HERE, ft_strdup(command[*y + 1])));
		simplecmd->hasheredoc = true;
		*y = *y + 2;
	}
	else if (ft_strcmp_n("\x1d", command[*y], 2) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(IN, ft_strdup(command[*y + 1])));
		*y = *y + 2;
	}
	return (0);
}

//this function checks if it is a append or a out-redirection
int	ft_outredirect(char **command, int *y, t_cmd *simplecmd, t_data *data)
{
	if (ft_strcmp_n("\x1c\x1c", command[*y], 3) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(APPEND, ft_strdup(command[*y + 1])));
		*y = *y + 2;
	}
	else if (ft_strcmp_n("\x1c", command[*y], 2) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(OUT, ft_strdup(command[*y + 1])));
		*y = *y + 2;
	}
	return (0);
}

//this function distinguishes between the in- and out- redirecitons
int	ft_distinguish(char **command, int *y, t_cmd *simplecmd, t_data *data)
{
	if (ft_strcmp_n("\x1d", command[*y], 2) == 0
		|| ft_strcmp_n("\x1d\x1d", command[*y], 3) == 0)
	{
		if (ft_inredirect(command, y, simplecmd, data) == -1)
			return (-1);
	}
	else if (ft_strcmp_n("\x1c", command[*y], 2) == 0
		|| ft_strcmp_n("\x1c\x1c", command[*y], 3) == 0)
	{
		if (ft_outredirect(command, y, simplecmd, data) == -1)
			return (-1);
	}
	return (0);
}

bool	ft_isredirection(char **command, int *y)
{
	if (ft_strcmp_n("\x1d", command[*y], 2) == 0
		|| ft_strcmp_n("\x1d\x1d", command[*y], 3) == 0
		|| ft_strcmp_n("\x1c", command[*y], 2) == 0
		|| ft_strcmp_n("\x1c\x1c", command[*y], 3) == 0)
		return (true);
	else
		return (false);
}

//this function helps freeing in case of error
void	ft_freepipecount(char **command, char **newcmd, t_slist	*cmdtable)
{
	freedchar(&command);
	freedchar(&newcmd);
	ft_free_commandlist(&cmdtable);
}
