/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:13:16 by aenglert          #+#    #+#             */
/*   Updated: 2021/06/29 19:13:16 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptrs;
	unsigned char	*ptrd;
	size_t			i;

	ptrs = (unsigned char *)src;
	ptrd = (unsigned char *)dst;
	if (!ptrs && !ptrd)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ptrd[i] = ptrs[i];
		i++;
	}
	return (dst);
}
