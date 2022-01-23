/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:46:46 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/28 12:27:47 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcpy_l(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src || !dst)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	while ((i < dstsize - 1) && (src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
