/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/21 17:31:39 by englot           ###   ########.fr       */
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

//this function write the ^C character to the screen
void	ctrlc(struct termios *termi, int flag)
{
	struct termios	termattr;

	termattr = *termi;
	if (flag == 0)
		termattr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termattr);
}

//this is the main signal handling for CTRL C & '\'
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
