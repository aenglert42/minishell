/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:43:33 by aenglert          #+#    #+#             */
/*   Updated: 2021/12/18 22:01:48 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	static_ft_count(char const *s, char c)
{
	size_t	i;
	int		words;

	words = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
	{
		i++;
	}
	while (i < ft_strlen(s))
	{
		while (s[i] != c)
		{
			if (s[i] == '\0')
			{
				words++;
				return (words);
			}
			i++;
		}
		i++;
		if (s[i] != c)
			words++;
	}
	return (words);
}

static int	static_ft_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		if (s[i] == '\0')
		{
			break ;
		}
		i++;
	}
	return (i);
}

static char	*static_ft_notchr(const char *s, int c)
{
	int			i;

	i = 0;
	while (s[i] == c && s[i] != '\0' )
	{
		i++;
	}
	return ((char *)s + i);
}

static int	static_ft_fill(char const *s, char c, int words, char **ptr)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (i < words)
	{
		str = static_ft_notchr(s, c);
		j = static_ft_len(str, c);
		ptr[i] = malloc(sizeof(char) * (j + 1));
		if (!ptr[i])
			return (0);
		ptr[i][j] = '\0';
		while (j > 0)
		{
			j--;
			ptr[i][j] = str[j];
		}
		s = str + static_ft_len(str, c) + 1;
		i++;
	}
	ptr[words] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**ptr;

	if (s == NULL)
		return (NULL);
	words = static_ft_count(s, c);
	ptr = malloc(sizeof(char *) * (words + 1));
	if (ptr == NULL)
		return (NULL);
	if (static_ft_fill(s, c, words, ptr) == 0)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
