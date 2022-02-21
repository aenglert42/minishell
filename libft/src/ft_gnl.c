/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 09:42:28 by aenglert          #+#    #+#             */
/*   Updated: 2022/02/21 20:51:54 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	static_ft_update(char *dst, char *src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int	static_ft_read(int fd, char *rem)
{
	int	rd;

	rd = read(fd, rem, BUFFER_SIZE);
	rem[rd] = '\0';
	return (rd);
}

static char	*static_ft_hasn(char *rem, char *line)
{
	char	*tmp;
	char	*newline;
	size_t	len;

	newline = ft_strchr(rem, '\n');
	len = newline + 1 - rem;
	tmp = ft_substr(rem, 0, len);
	if (!tmp)
		return (NULL);
	line = ft_strappend(line, tmp);
	free(tmp);
	if (!line)
		return (NULL);
	static_ft_update(rem, newline + 1);
	return (line);
}

static char	*static_ft_checkline(char *line)
{
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_gnl(int fd)
{
	static char		rem[BUFFER_SIZE + 1];
	char			*line;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	*line = '\0';
	while (1)
	{
		if (ft_strchr(rem, '\n'))
			return (static_ft_hasn(rem, line));
		else if (!*rem)
		{
			if (static_ft_read(fd, rem) <= 0)
				return (static_ft_checkline(line));
		}
		else
		{
			line = ft_strappend(line, rem);
			if (!line)
				return (NULL);
			*rem = '\0';
		}
	}
}
