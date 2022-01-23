/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:10:16 by aenglert          #+#    #+#             */
/*   Updated: 2021/06/30 15:10:16 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	static_ft_isset(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	static_ft_fill(char *ptr, char const *str, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		len;

	if (!s1 || !set)
		return (0);
	len = ft_strlen(s1);
	while (len > 0 && static_ft_isset(s1[len - 1], set) == 1)
	{
		len--;
	}
	while (len > 0 && static_ft_isset(*s1, set) == 1)
	{
		s1++;
		len--;
	}
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	static_ft_fill(ptr, s1, len);
	return (ptr);
}
