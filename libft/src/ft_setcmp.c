/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:24:48 by aenglert          #+#    #+#             */
/*   Updated: 2021/11/25 11:26:37 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_setcmp(char c, char *set)
{
	if (set == NULL)
		return (false);
	while (*set)
	{
		if (c == *set)
			return (true);
		set++;
	}
	return (false);
}
