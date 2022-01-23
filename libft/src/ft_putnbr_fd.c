/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:11:03 by aenglert          #+#    #+#             */
/*   Updated: 2021/06/30 15:11:03 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_unsigned;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_unsigned = -n;
	}
	else
	{
		n_unsigned = n;
	}
	if (n_unsigned >= 10)
	{
		ft_putnbr_fd(n_unsigned / 10, fd);
		ft_putnbr_fd(n_unsigned % 10, fd);
	}
	else
		ft_putchar_fd(n_unsigned + '0', fd);
}
