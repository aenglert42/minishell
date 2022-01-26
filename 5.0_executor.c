/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.0_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:20:45 by englot            #+#    #+#             */
/*   Updated: 2022/01/26 19:32:15 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_ft_wait_processes(t_data *data)
{
	t_slist	*ptr;
	int		count;

	count = 1;
	ptr = data->commands;
	while (ptr != NULL)
	{
		waitpid(((t_cmd *)ptr->content)->pid, &data->lastexitstatus, 0);
		ptr = ptr->next;
		count++;
	}
	if (WTERMSIG(data->lastexitstatus))
		data->lastexitstatus = WTERMSIG(data->lastexitstatus) + 128;
	else if (WIFEXITED(data->lastexitstatus))
		data->lastexitstatus = WEXITSTATUS(data->lastexitstatus);
}

static void	static_ft_set_pipe(t_slist *cmdlist, t_data *data)
{
	if (cmdlist->next != NULL)
	{
		if (pipe(data->mypipe) == -1)
			ft_exit_errno(data);
	}
	((t_cmd *)cmdlist->content)->fd[READ] = data->tmp_fd[0];
	((t_cmd *)cmdlist->content)->fd[WRITE] = data->mypipe[WRITE];
}

static void	static_ft_create_children(t_data *data)
{
	t_slist	*cmdlist;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, &sighandler);
	cmdlist = data->commands;
	while (cmdlist != NULL)
	{
		static_ft_set_pipe(cmdlist, data);
		((t_cmd *)cmdlist->content)->pid = fork();
		if (((t_cmd *)cmdlist->content)->pid == -1)
			ft_exit(data);
		else if (((t_cmd *)cmdlist->content)->pid == 0)
			ft_childprocess(cmdlist, data);
		close(data->mypipe[WRITE]);
		close(data->tmp_fd[0]);
		dup2(data->mypipe[READ], data->tmp_fd[0]);
		close(data->mypipe[READ]);
		cmdlist = cmdlist->next;
	}
}

static void	static_ft_execute_builtin_in_parent(t_data *data)
{
	data->tmp_fd[1] = dup(STDOUT_FILENO);
	if (data->tmp_fd[1] == -1)
		ft_exit_errno(data);
	ft_child_redirect_std_fds(((t_cmd *)data->commands->content), data);
	if (((t_cmd *)data->commands->content)->fd[READ] != STDIN_FILENO)
	{
		if (dup2(((t_cmd *)data->commands->content)->fd[READ],
				STDIN_FILENO) == -1)
			ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
		close(((t_cmd *)data->commands->content)->fd[READ]);
	}
	if (((t_cmd *)data->commands->content)->fd[WRITE] != STDOUT_FILENO)
	{
		if (dup2(((t_cmd *)data->commands->content)->fd[WRITE],
				STDOUT_FILENO) == -1)
			ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
		close(((t_cmd *)data->commands->content)->fd[WRITE]);
	}
	ft_execute_builtin(data->commands, data);
	dup2(data->tmp_fd[0], STDIN_FILENO);
	dup2(data->tmp_fd[1], STDOUT_FILENO);
	close(data->tmp_fd[0]);
	close(data->tmp_fd[1]);
}

void	ft_execute(t_data *data)
{
	if (data->commands == NULL)
		ft_exit(data);
	ft_get_heredoc_input(data);
	data->tmp_fd[0] = dup(STDIN_FILENO);
	if (data->tmp_fd[0] == -1)
		ft_exit_errno(data);
	if (data->commands->next == NULL
		&& ((t_cmd *)data->commands->content)->isbuiltin)
		static_ft_execute_builtin_in_parent(data);
	else
	{
		static_ft_create_children(data);
		close(data->tmp_fd[0]);
		static_ft_wait_processes(data);
	}
	ft_free_commandlist(&data->commands);
}
