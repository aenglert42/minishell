/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:06:17 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_builtin(t_slist *cmdlist, t_data *data)
{
	t_cmd	*cmd;

	cmd = ((t_cmd *)cmdlist->content);
	if (ft_strcmp(cmd->path, "echo"))
		data->lastexitstatus = builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->path, "cd"))
		data->lastexitstatus = builtin_cd(&data->myenv, cmd->args);
	else if (ft_strcmp(cmd->path, "pwd"))
		data->lastexitstatus = builtin_pwd();
	else if (ft_strcmp(cmd->path, "export"))
	{
		if ((cmd->args != NULL) && (cmd->args[1] == NULL))
			data->lastexitstatus = builtin_env(data->myenv, true);
		else
			data->lastexitstatus = builtin_export(&data->myenv, cmd->args);
	}
	else if (ft_strcmp(cmd->path, "unset"))
		data->lastexitstatus = builtin_unset(data->myenv, cmd->args);
	else if (ft_strcmp(cmd->path, "env"))
		data->lastexitstatus = builtin_env(data->myenv, false);
	else
		data->lastexitstatus = builtin_exit(data, cmd->args);
	if (data->commands->next != NULL)
		ft_free_data_struct_content(data);
	return (data->lastexitstatus);
}

int	ft_get_myenv_index(char **myenv, char *var)
{
	int			i;

	if (myenv == NULL)
		return (ERROR);
	i = 0;
	while (myenv[i] != NULL)
	{
		if (!ft_strcmp_n(myenv[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (ERROR);
}

void	ft_dlstdel(void *content)
{
	free(content);
}

int	ft_exchange_envvar(int i, char **myenv, char *replacement)
{
	char	*tmp;

	tmp = ft_strdup(replacement);
	if (tmp == NULL)
		return (ft_errormessage(strerror(errno)));
	else
	{
		free(myenv[i]);
		myenv[i] = tmp;
	}
	return (EXIT_SUCCESS);
}

char	*ft_child_search_myenv(char **myenv, char *var)
{
	int			i;

	if (myenv == NULL)
		return (NULL);
	i = 0;
	while (myenv[i] != NULL)
	{
		if (!ft_strcmp_n(myenv[i], var, ft_strlen(var)))
			return (myenv[i]);
		i++;
	}
	return (NULL);
}
