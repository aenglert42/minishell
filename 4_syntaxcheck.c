/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_syntaxcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzhou <jzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/20 11:39:38 by jzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntaxerr(t_data *data)
{
	data->lastexitstatus = 2;
	printf("syntax error near unexpected token 'newline'\n");
}

bool	ft_syntaxcheck(t_data *data)
{
	data->lastexitstatus = 2;
	printf("empty commandtable\n");
	return (true);
}
