/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.2_childprocesses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:16:00 by englot            #+#    #+#             */
/*   Updated: 2021/12/21 17:30:37 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*static_ft_append_commandname(char *path, char *str)
{
	ft_strappend2(&path, "/");
	ft_strappend2(&path, str);
	return (path);
}

static char	*static_ft_child_get_path(char *str, t_data *data)
{
	char		*ret;
	char		**paths;
	int			i;

	ret = ft_child_search_myenv(data->myenv, "PATH=");
	if (ret == NULL)
		return (NULL);
	paths = ft_split(ret + ft_strlen("PATH="), ':');
	if (paths == NULL)
		ft_exit_errno(data);
	i = 0;
	ret = NULL;
	while (paths[i] != NULL)
	{
		paths[i] = static_ft_append_commandname(paths[i], str);
		if (paths[i] == NULL)
			ft_exit_errno(data);
		if (access(paths[i], X_OK) != -1 && ret == NULL)
			ret = paths[i];
		else
			free(paths[i]);
		i++;
	}
	free(paths);
	return (ret);
}

static void	static_ft_child_execve(t_slist *cmdlist, t_data *data, char	*tmp)
{
	tmp = ((t_cmd *)cmdlist->content)->path;
	if (ft_strchr(tmp, '/') == NULL)
	{
		((t_cmd *)cmdlist->content)->path = static_ft_child_get_path(tmp, data);
		free(tmp);
	}
	if (((t_cmd *)cmdlist->content)->path != NULL)
	{
		if (execve(((t_cmd *)cmdlist->content)->path,
				((t_cmd *)cmdlist->content)->args, data->myenv) == -1)
		{
			if (errno == ENOENT)
				ft_printf_stderr("%s: %s %s\n", SHELL, "command not found:",
					((t_cmd *)cmdlist->content)->args[0]);
			else
				ft_printf_stderr("%s: %s %s\n", SHELL, strerror(errno),
					((t_cmd *)cmdlist->content)->args[0]);
			ft_free_data_struct_content(data);
			exit (NOTDEFINED);
		}
	}
	ft_printf_stderr("%s: %s %s\n", SHELL, "command not found:",
		((t_cmd *)cmdlist->content)->args[0]);
	ft_free_data_struct_content(data);
	exit (NOTDEFINED);
}

int	ft_child_piping(t_slist *cmdlist, t_data *data)
{
	if ((dup2(((t_cmd *)cmdlist->content)->fd[READ], STDIN_FILENO)) == -1)
		ft_exit_errno(data);
	close(((t_cmd *)cmdlist->content)->fd[READ]);
	if ((dup2(((t_cmd *)cmdlist->content)->fd[WRITE], STDOUT_FILENO)) == -1)
	{
		if (errno != EBADF)
			ft_exit_errno(data);
	}
	close(((t_cmd *)cmdlist->content)->fd[WRITE]);
	return (EXIT_SUCCESS);
}

void	ft_childprocess(t_slist *cmdlist, t_data *data)
{
	char	*tmppath;

	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	tmppath = NULL;
	ft_child_redirect_std_fds(((t_cmd *)cmdlist->content), data);
	ft_child_piping(cmdlist, data);
	close(data->mypipe[READ]);
	close(data->mypipe[WRITE]);
	close(data->tmp_fd[0]);
	if (((t_cmd *)cmdlist->content)->isbuiltin)
		exit(ft_execute_builtin(cmdlist, data));
	else
		static_ft_child_execve(cmdlist, data, tmppath);
}
