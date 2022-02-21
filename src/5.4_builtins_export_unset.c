/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_export_unset.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:06:38 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	static_ft_recreate_myenv(char ***myenv, char *newvar)
{
	int		count;
	int		i;
	char	**newenv;

	count = 0;
	while (*myenv != NULL && (*myenv)[count] != NULL)
		count++;
	newenv = malloc((count + 2) * sizeof(char *));
	if (newenv == NULL)
		return (ft_errormessage(strerror(errno)));
	i = 0;
	while (i < count)
	{
		newenv[i] = ft_strdup((*myenv)[i]);
		if (newenv[i] == NULL)
			return (ft_errormessage(strerror(errno)));
		i++;
	}
	newenv[i] = ft_strdup(newvar);
	newenv[i + 1] = NULL;
	freedchar(myenv);
	*myenv = newenv;
	return (EXIT_SUCCESS);
}

static int	static_ft_is_valid_identifier(char **identifier)
{
	int	i;

	if (!ft_isalpha((*identifier)[0]) && (*identifier)[0] != '_')
		return (false);
	i = 1;
	while ((*identifier)[i] != '\0' && (*identifier)[i] != '=')
	{
		if (!ft_is_valid_char((*identifier)[i]))
			return (false);
		i++;
	}
	if ((*identifier)[i] == '\0')
	{
		if (ft_strappend2(identifier, "="))
		{
			ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
			return (ERROR);
		}
		i++;
	}
	return (i);
}

static int	static_ft_update_myenv(char ***myenv, char *arg, int len)
{
	char	*varname;
	int		index;

	varname = ft_substr(arg, 0, len);
	index = ft_get_myenv_index(*myenv, varname);
	free(varname);
	varname = NULL;
	if (index != ERROR)
	{
		if (ft_exchange_envvar(index, *myenv, arg))
			return (EXIT_FAILURE);
	}
	else
	{
		if (static_ft_recreate_myenv(myenv, arg))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//not alphabetical
//args[1] in format NAME=[CONTENT] (without spaces)
//following args get ignored
//is used by builtin_cd to set OLDPWD and PWD
//no argument case not handeled as it equals (export -p)
int	builtin_export(char ***myenv, char **args)
{
	int		len;
	int		i;
	int		ret;

	if (args == NULL)
		return (EXIT_SUCCESS);
	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i] != NULL)
	{
		len = static_ft_is_valid_identifier(&args[i]);
		if (len == 0)
		{
			ft_printf_stderr("%s: export: `%s': not a valid identifier\n",
				SHELL, args[i]);
			ret = EXIT_FAILURE;
		}
		else
		{
			if (len == ERROR || static_ft_update_myenv(myenv, args[i], len))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (ret);
}

int	builtin_unset(char **myenv, char **args)
{
	int	i;
	int	pos;

	if (myenv == NULL || args == NULL)
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i] != NULL)
	{
		pos = ft_get_myenv_index(myenv, args[i]);
		if (pos == ERROR)
			return (EXIT_SUCCESS);
		free(myenv[pos]);
		while (myenv[pos + 1] != NULL)
		{
			myenv[pos] = myenv[pos + 1];
			pos++;
		}
		myenv[pos] = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}
