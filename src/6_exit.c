/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:24:50 by englot            #+#    #+#             */
/*   Updated: 2022/02/25 22:37:44 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_tokenizer(t_data *data, t_slist **tokens)
{
	ft_syntaxerr(data);
	ft_lstclear(tokens, &ft_del);
	return (EXIT_FAILURE);
}

void	ft_exit_expander(t_slist **slist, char **token, char **myenv)
{
	ft_printf_stderr("%s: Error: %s\n", SHELL, strerror(errno));
	ft_lstclear(slist, ft_del);
	free(*token);
	freedchar(&myenv);
	exit (EXIT_FAILURE);
}

void	ft_exit(t_data *data)
{
	ft_free_data_struct_content(data);
	exit (EXIT_FAILURE);
}

void	ft_exit_errno(t_data *data)
{
	ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
	ft_exit(data);
}
