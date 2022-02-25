/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.4_syntaxcheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:54:52 by englot            #+#    #+#             */
/*   Updated: 2022/02/25 22:32:36 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntaxerr(t_data *data)
{
	data->lastexitstatus = SYNTAX;
	ft_printf_stderr("%s: syntax error near unexpected token\n", SHELL);
}

bool	ft_syntaxcheck(t_data *data)
{
	data->lastexitstatus = SYNTAX;
	ft_printf_stderr("%s: syntax error near unexpected token\n", SHELL);
	return (true);
}
