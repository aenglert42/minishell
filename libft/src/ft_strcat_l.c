/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:07:19 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/28 12:27:26 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcat_l(char *dst, const char *src, size_t dstsize)
{
	size_t	ld;
	size_t	i;
	size_t	ls;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (dstsize <= ld)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (ld < dstsize - 1 && src[i] != '\0')
	{
		dst[ld] = src[i];
		ld++;
		i++;
	}
	dst[ld] = '\0';
	return (ft_strlen(dst) + ls - i);
}
