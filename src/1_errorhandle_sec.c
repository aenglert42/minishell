/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_errorhandle_sec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/21 20:46:31 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// //here >< and <> will be checked
// bool	ft_nonsense(char **command)
// {
// 	int	y;

// 	y = 0;
// 	while (command[y] != NULL)
// 	{
// 		if (command[y][0] == '>' && command[y][1] == '<')
// 			return (true);
// 		else if (command[y][0] == '<' && command[y][1] == '>')
// 			return (true);
// 		y++;
// 	}
// 	return (false);
// }

// //this function checks if a number is odd or even
// /*
// bool	ft_iseven(int nbr)
// {
// 	if (nbr % 2 == 0 || nbr == 0)
// 		return (true);
// 	else
// 		return (false);
// }*/

// //this function returns a char *
// char	*ft_quoteerror(t_data *data)
// {
// 	data->lastexitstatus = 2;
// 	printf("missing quotes\n");
// 	return (NULL);
// }
