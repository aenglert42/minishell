/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrret_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:44:56 by aenglert          #+#    #+#             */
/*   Updated: 2021/09/28 17:00:28 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrret_fd(char *s, int fd)
{
	if (s == NULL)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}
