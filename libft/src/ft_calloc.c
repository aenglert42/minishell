/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:11:54 by aenglert          #+#    #+#             */
/*   Updated: 2021/06/30 15:11:54 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)(malloc(count * size));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *) ptr);
}
