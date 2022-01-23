/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:51:18 by aenglert          #+#    #+#             */
/*   Updated: 2021/06/29 19:51:18 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptrd;
	const char	*ptrs;
	size_t		i;

	ptrd = (char *)dst;
	ptrs = (const char *)src;
	if (!ptrd && !ptrs)
		return (NULL);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	if (dst >= src)
	{
		i = len;
		while (i-- != 0)
			ptrd[i] = ptrs[i];
	}
	return ((void *)dst);
}
