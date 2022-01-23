/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_tokenizer_trd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/22 12:05:59 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function allocates the memory needed for creating
//the char **command for the first time with spaces included
char	**ft_allocfsttime(char **command, int y, int malloccounter)
{
	char	**finalcmd;

	finalcmd = NULL;
	while (command[y] != NULL)
	{
		while (command[y] != NULL && (command[y][0] == '>'
			|| command[y][0] == '<'))
			y++;
		malloccounter++;
		if (command[y] == NULL)
			break ;
		y++;
		malloccounter++;
	}
	malloccounter++;
	finalcmd = (char **)malloc(malloccounter * sizeof(char *));
	return (finalcmd);
}

//this function merges > and > to >>, as well as < and < to <<
char	**ft_merging(char **command, int y, int malloccounter, char **finalcmd)
{
	while (command[y] != NULL)
	{
		finalcmd[malloccounter] = ft_strdup("");
		if (command[y] != NULL && (command[y][0] == '>'
			|| command[y][0] == '<'))
		{
			ft_mergeall(command, finalcmd, &y, &malloccounter);
		}
		if (command[y] == NULL)
			break ;
		else if (command[y][0] != '>' && command[y][0] != '<')
		{
			finalcmd[malloccounter] = ft_strdup(command[y]);
			y++;
			malloccounter++;
		}
	}
	finalcmd[malloccounter] = NULL;
	return (finalcmd);
}

//this function controls the merging function
char	**ft_merge_redirect(char **command, t_data *data)
{
	int		y;
	int		malloccounter;
	char	**finalcmd;
	char	**temp;

	y = 0;
	malloccounter = 0;
	finalcmd = ft_allocfsttime(command, y, malloccounter);
	if (finalcmd == NULL)
		return (NULL);
	temp = ft_merging(command, y, malloccounter, finalcmd);
	if (ft_nonsense(temp))
		return (ft_errorstr(data, temp));
	return (temp);
}

//this function allocates the memory for the char **command without spaces
char	**ft_allocnospace(char **command)
{
	int		y;
	int		malloccounter;
	char	**finalcmd;

	y = 0;
	malloccounter = 0;
	while (command[y] != NULL)
	{
		if (command[y][0] == ' ')
			y++;
		else
		{
			malloccounter++;
			y++;
		}
	}
	malloccounter++;
	finalcmd = (char **)malloc(malloccounter * sizeof(char *));
	return (finalcmd);
}

//this function erases the spaces between the commands
char	**ft_erasespace(char **command, char **finalcmd)
{
	int	y;
	int	malloccounter;

	y = 0;
	malloccounter = 0;
	while (command[y] != NULL)
	{
		if (command[y][0] == ' ')
			y++;
		else
		{
			finalcmd[malloccounter] = ft_strdup(command[y]);
			malloccounter++;
			y++;
		}
	}
	finalcmd[malloccounter] = NULL;
	return (finalcmd);
}
