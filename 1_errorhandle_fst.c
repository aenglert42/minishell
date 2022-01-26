/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_errorhandle_fst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/01/26 09:41:03 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// //here we run our first errorcheck to see if there are >>> or <<<

// /*
// //this function returns a t_slist-error
// t_slist	*ft_errortoken(char *s, t_slist **tokenlst)
// {
// 	//set data struct exitcode = 2;
// 	if (s)
// 		printf("%s\n", s);
// 	if (tokenlst)
// 		ft_lstclear(tokenlst, ft_del);
// 	return (*tokenlst);
// }*/

// //this function returns the string error
// char	**ft_errorstr(t_data *data, char **finalcmd)
// {
// 	data->lastexitstatus = 2;
// 	printf("syntax error near unexpected token 'newline'\n");
// 	if (finalcmd)
// 	{
// 		freedchar(&finalcmd);
// 		finalcmd = NULL;
// 	}
// 	return (finalcmd);
// }

// //this function returns the int error
// int	ft_errorint(t_data *data)
// {
// 	data->lastexitstatus = 2;
// 	printf("syntax error near unexpected token > or <\n");
// 	return (1);
// }

// //this function checks for 
// bool	ft_redirections(t_slist *temp)
// {
// 	if (ft_strcmp_n(temp->content, ">", 2) == 0
// 		|| ft_strcmp_n(temp->content, "<", 2) == 0)
// 		return (true);
// 	return (false);
// }

// //this function checks for too many redirection symbols
// bool	ft_triple_re(t_slist *tokenlst, t_data *data)
// {
// 	t_slist	*temp;
// 	int		counter;

// 	counter = 0;
// 	temp = tokenlst;
// 	while (temp != NULL)
// 	{
// 		while (temp != NULL && ft_redirections(temp))
// 		{
// 			counter++;
// 			temp = temp->next;
// 		}
// 		if (temp == NULL)
// 			break ;
// 		temp = temp->next;
// 		counter = 0;
// 	}
// 	if (counter > 2)
// 	{
// 		ft_errorint(data);
// 		return (true);
// 	}
// 	return (false);
// }
