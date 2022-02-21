/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.2_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:04:22 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	static_ft_trim_two(char **str, int i)
{
	int	count;

	count = 2;
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
	return (0);
}

static int	static_ft_fetchexitcode(t_slist **list,	int lastExitStatus)
{
	t_slist	*tmp;
	char	*str;

	str = ft_itoa(lastExitStatus);
	tmp = ft_lstnew(str);
	if (tmp == NULL || str == NULL)
	{
		free (str);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(list, tmp);
	return (EXIT_SUCCESS);
}

void	ft_determine_expansion_type(char **token, t_index *index,
	t_slist **parts, t_data *data)
{
	if ((*token)[index->i + 1] == '?')
	{
		if (static_ft_fetchexitcode(parts, data->lastexitstatus))
			ft_exit_expander(parts, token, data->myenv);
		index->i = index->i + 2;
		index->pos = index->i;
	}
	else if (ft_isdigit((*token)[index->i + 1]))
	{
		index->i = index->i + static_ft_trim_two(token, index->i);
		index->pos = index->i;
	}
	else if (ft_is_valid_char((*token)[index->i + 1]))
	{
		index->i = index->i + ft_expand_var(token,
				index->i, parts, data->myenv);
		index->pos = index->i;
	}
	else
		index->i = index->i + 1;
}
