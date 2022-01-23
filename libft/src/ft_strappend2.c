/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:10:40 by aenglert          #+#    #+#             */
/*   Updated: 2021/06/30 15:10:40 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	static_ft_create_str(char *s1, char const *s2, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
}

int	ft_strappend2(char **s1, char const *s2)
{
	char	*str;

	if (*s1 == NULL || s2 == NULL)
	{
		free (*s1);
		*s1 = NULL;
		return (EXIT_FAILURE);
	}
	str = malloc(ft_strlen(*s1) + ft_strlen(s2) + 1);
	if (str == NULL)
	{
		free (*s1);
		*s1 = NULL;
		return (EXIT_FAILURE);
	}
	static_ft_create_str(*s1, s2, str);
	free (*s1);
	*s1 = str;
	return (EXIT_SUCCESS);
}
