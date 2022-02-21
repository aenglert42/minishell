/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.3_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:04:36 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_ft_trim_nonexisting(char **str, int i)
{
	int	count;

	count = 1;
	while (ft_is_valid_char((*str)[i + count]) && (*str)[i + count] != '\0')
		count++;
	while ((*str)[i + count] != '\0')
	{
		(*str)[i] = (*str)[i + count];
		i++;
	}
	while ((*str)[i] != '\0')
	{
		(*str)[i] = '\0';
		i++;
	}
}

static int	static_ft_extract_var(int i, int len, t_slist **list, char **myenv)
{
	t_slist		*tmp;
	int			diff;
	char		*ptr;

	diff = ft_strlen(myenv[i] + len + 1);
	ptr = ft_substr(myenv[i], len + 1, diff);
	tmp = ft_lstnew(ptr);
	if (tmp == NULL || tmp->content == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(list, tmp);
	return (EXIT_SUCCESS);
}

int	ft_expand_var(char **token, int start, t_slist **parts, char **myenv)
{
	int			i;
	int			len;

	i = 0;
	while (myenv[i] != NULL)
	{
		len = 0;
		while (myenv[i][len] != '\0')
		{
			if (myenv[i][len] == '='
				&& (!ft_is_valid_char((*token)[start + 1 + len])))
			{
				if (static_ft_extract_var(i, len, parts, myenv))
					ft_exit_expander(parts, token, myenv);
				return (len + 1);
			}
			else if (myenv[i][len] != (*token)[start + 1 + len])
				break ;
			len++;
		}
		i++;
	}
	static_ft_trim_nonexisting(token, start);
	return (0);
}
