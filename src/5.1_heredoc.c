/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:16:53 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_heredoc_error_message(t_re *redirection, t_data *data, int i)
{
	if (errno != 0)
	{
		if (errno != EBADF)
			ft_exit_errno(data);
	}
	else
		ft_printf_stderr("%s: warning: here-document at line %d "
			"delimited by end-of-file (wanted `%s')\n",
			SHELL, i, redirection->file);
}

static void	static_read_from_terminal(t_re *redirection, t_data *data)
{
	char	*line;
	int		i;

	i = 1;
	while (1)
	{
		line = readline(HEREPROMPT);
		if (line == NULL)
		{
			static_heredoc_error_message(redirection, data, i);
			break ;
		}
		if (ft_strcmp(line, redirection->file))
			break ;
		write(redirection->herepipe[WRITE], line, ft_strlen(line));
		write(redirection->herepipe[WRITE], "\n", 1);
		free(line);
		line = NULL;
		i++;
	}
	free(line);
}

static void	static_ft_here_doc(t_re *redirection, t_data *data)
{
	int		fd;

	fd = dup(STDIN_FILENO);
	if (pipe(redirection->herepipe) == -1)
		ft_exit_errno(data);
	signal(SIGINT, &ft_sigfunc_here_doc);
	signal(SIGQUIT, SIG_IGN);
	static_read_from_terminal(redirection, data);
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
	close(redirection->herepipe[WRITE]);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_exit_errno(data);
}

void	ft_get_heredoc_input(t_data *data)
{
	t_slist	*cmdlist;
	t_re	*tmp;

	cmdlist = data->commands;
	while (cmdlist != NULL)
	{
		tmp = ((t_cmd *)cmdlist->content)->re;
		while (tmp != NULL)
		{
			if (tmp->operator == HERE)
				static_ft_here_doc(tmp, data);
			tmp = tmp->next;
		}
		cmdlist = cmdlist->next;
	}
}
