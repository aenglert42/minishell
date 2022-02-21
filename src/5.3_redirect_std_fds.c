/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.3_redirect_std_fds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:08:27 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	static_ft_child_redirect_in(t_re *redirection, t_data *data)
{
	int	fd;

	fd = open(redirection->file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		ft_exit(data);
	}
	return (fd);
}

static int	static_ft_child_redirect_out(t_re *redirection, t_data *data)
{
	int	fd;

	fd = open(redirection->file, O_WRONLY | O_CREAT | O_TRUNC,
			RWRR);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		ft_exit(data);
	}
	return (fd);
}

static int	static_ft_child_redirect_append(t_re *redirection, t_data *data)
{
	int	fd;

	fd = open(redirection->file, O_WRONLY | O_CREAT | O_APPEND,
			RWRR);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		ft_exit(data);
	}
	return (fd);
}

int	ft_child_redirect_std_fds(t_cmd *cmd, t_data *data)
{
	t_re	*reptr;

	reptr = cmd->re;
	while (reptr != NULL)
	{
		if (reptr->operator == IN)
		{
			cmd->fd[READ] = static_ft_child_redirect_in(reptr, data);
		}
		else if (reptr->operator == OUT)
		{
			cmd->fd[WRITE] = static_ft_child_redirect_out(reptr, data);
		}
		else if (reptr->operator == APPEND)
		{
			cmd->fd[WRITE] = static_ft_child_redirect_append(reptr, data);
		}
		else
			cmd->fd[READ] = reptr->herepipe[READ];
		reptr = reptr->next;
	}
	return (EXIT_SUCCESS);
}
