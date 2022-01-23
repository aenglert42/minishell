/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_quote_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:23:32 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/21 23:45:32 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function scans for single and double quotes (' ' & " ")
int	ft_scanforq(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '\'')
			return (7);
		else if (s[i] == '"')
			return (8);
		i++;
	}
	return (9);
}

void	ft_quotehelper(char *s, int *k, int *i)
{
	s[*k] = s[*i];
	(*k)++;
	(*i)++;
}

//this function erases quotes
char	*ft_erasequotes(char *s, int i, int k)
{
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				ft_quotehelper(s, &k, &i);
			i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '"')
				ft_quotehelper(s, &k, &i);
			i++;
		}
		else
			ft_quotehelper(s, &k, &i);
	}
	s[k] = '\0';
	return (s);
}

//this function allocates and duplicates the new command without quotes
char	**ft_noquotes(char **command, int y, int j, char **finalcmd)
{
	while (command[j] != NULL)
		j++;
	j++;
	finalcmd = (char **)malloc(j * sizeof(char *));
	if (finalcmd == NULL)
		return (NULL);
	j = 0;
	while (command[j] != NULL)
	{
		if (ft_scanforq(command[j]) == 7 || ft_scanforq(command[j]) == 8)
			finalcmd[y] = ft_erasequotes(command[j], 0, 0);
		else
			finalcmd[y] = ft_strdup(command[j]);
		y++;
		j++;
	}
	finalcmd[y] = NULL;
	return (finalcmd);
}

//this is the main function to return a command without quotes
char	**ft_removeq(char **command)
{
	int		y;
	int		j;
	char	**finalcmd;
	char	**s;

	y = 0;
	j = 0;
	finalcmd = NULL;
	s = ft_noquotes(command, y, j, finalcmd);
	return (s);
}
