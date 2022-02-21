/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.2_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:24:50 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_errormessage(char *builtin, char *message)
{
	ft_printf_stderr("%s: %s: %s\n", SHELL, builtin, message);
	return (EXIT_FAILURE);
}

int	ft_errormessage(char *message)
{
	ft_printf_stderr("%s: %s\n", SHELL, message);
	return (EXIT_FAILURE);
}

char	*ft_error_dlst(t_dlist **dlist)
{
	ft_dlstclear(dlist, &ft_dlstdel);
	return (NULL);
}
