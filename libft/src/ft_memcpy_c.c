/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpyc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:13:16 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/28 12:25:09 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_c(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*ptrs;
	unsigned char		*ptrd;
	size_t				i;

	ptrs = (unsigned char *)src;
	ptrd = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		ptrd[i] = ptrs[i];
		if (ptrs[i] == (unsigned char)c)
		{
			return (ptrd + i + 1);
		}
		i++;
	}
	return (0);
}
