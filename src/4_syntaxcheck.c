/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_syntaxcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/21 20:46:31 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
