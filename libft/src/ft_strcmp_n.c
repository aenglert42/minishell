/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:10:29 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/28 12:28:08 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_n(const char *str1, const char *str2, size_t n)
{
	unsigned int	count;

	count = 0;
	while (count < n)
	{
		if ((unsigned char)str1[count] != (unsigned char)str2[count])
		{
			return ((unsigned char)str1[count] - (unsigned char)str2[count]);
		}
		if ((unsigned char)str1[count] == '\0'
			|| (unsigned char)str2[count] == '\0')
		{
			return (0);
		}
		count++;
	}
	return (0);
}
