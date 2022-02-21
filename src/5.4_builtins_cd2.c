/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_cd2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:08:06 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*static_ft_create_curpath_str(char *curpath, t_dlist **list)
{
	t_dlist	*tmp;

	free(curpath);
	curpath = ft_strdup("/");
	if (curpath == NULL)
		return (ft_error_dlst(list));
	tmp = *list;
	while (tmp != NULL)
	{
		ft_strappend2(&curpath, tmp->content);
		if (tmp->next != NULL)
			ft_strappend2(&curpath, "/");
		if (curpath == NULL)
			return (ft_error_dlst(list));
		tmp = tmp->next;
	}
	ft_dlstclear(list, &ft_dlstdel);
	return (curpath);
}

static void	static_ft_remove_dots(t_dlist **list)
{
	t_dlist	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (!ft_strcmp_n((char *)tmp->content, ".", 2))
		{
			ft_dlstremove_node(list, tmp, &ft_dlstdel);
			tmp = *list;
		}
		else if (!ft_strcmp_n((char *)tmp->content, "..", 3))
		{
			if (tmp->prev != NULL)
				ft_dlstremove_node(list, tmp->prev, &ft_dlstdel);
			ft_dlstremove_node(list, tmp, &ft_dlstdel);
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
}

static char	*static_ft_convert_to_canonical(char *curpath)
{
	char	**components;
	int		i;
	t_dlist	*list;
	t_dlist	*tmp;

	list = NULL;
	components = ft_split(curpath, '/');
	if (components == NULL)
		return (NULL);
	i = 0;
	while (components[i] != NULL)
	{
		tmp = ft_dlstnew(components[i]);
		if (tmp == NULL)
		{
			free(components);
			return (ft_error_dlst(&list));
		}
		ft_dlstadd_back(&list, tmp);
		i++;
	}
	free(components);
	static_ft_remove_dots(&list);
	curpath = static_ft_create_curpath_str(curpath, &list);
	return (curpath);
}

static int	static_ft_get_cwd(char **pwd)
{
	int	i;

	*pwd = getcwd(NULL, 0);
	if (*pwd == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while ((*pwd)[i] != '\0' && (*pwd)[i + 1] != '\0')
		i++;
	if ((*pwd)[i] != '/')
	{
		if (ft_strappend2(pwd, "/"))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_construct_dir(char **curpath, char *arg)
{
	char	*pwd;

	if (arg[0] == '/')
	{
		*curpath = ft_strdup(arg);
		if (*curpath == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		if (static_ft_get_cwd(&pwd))
			return (EXIT_FAILURE);
		if (ft_strappend2(&pwd, arg))
			return (EXIT_FAILURE);
		*curpath = static_ft_convert_to_canonical(pwd);
		if (*curpath == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
