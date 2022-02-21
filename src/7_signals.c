/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:56:31 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigfunc_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		close(STDIN_FILENO);
	}
}

void	ctrlc(struct termios *termi, int flag)
{
	struct termios	termattr;

	termattr = *termi;
	if (flag == 0)
		termattr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termattr);
}

void	sighandler(int sig)
{
	char	*tmp;

	if (sig == SIGQUIT)
	{
		tmp = "^\\Quit (core dumped)";
		write(STDOUT_FILENO, tmp, ft_strlen(tmp));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
