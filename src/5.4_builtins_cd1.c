/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_cd1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:08:18 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_ft_free_pwds_array(char **pwds)
{
	free(pwds[1]);
	pwds[1] = NULL;
	free(pwds[2]);
	pwds[2] = NULL;
}

static int	static_ft_change_dir(char ***myenv, char *curpath, char *arg)
{
	char	*pwds[4];

	pwds[3] = NULL;
	pwds[0] = getcwd(NULL, 0);
	if (pwds[0] == NULL)
		return (ERROR);
	if (chdir(curpath) == -1)
	{
		ft_printf_stderr("%s: cd: %s: %s\n", SHELL, arg, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (arg != NULL && !ft_strcmp_n(arg, "-", 2))
		printf("%s\n", curpath);
	pwds[1] = ft_strjoin("OLDPWD=", pwds[0]);
	free(pwds[0]);
	pwds[2] = ft_strjoin("PWD=", curpath);
	if (pwds[1] == NULL || pwds[2] == NULL)
	{
		static_ft_free_pwds_array(pwds);
		return (ERROR);
	}
	builtin_export(myenv, pwds);
	static_ft_free_pwds_array(pwds);
	return (EXIT_SUCCESS);
}

static int	static_ft_handle_cd_oldpwd(char **myenv, char **curpath)
{
	if (ft_child_search_myenv(myenv, "OLDPWD") != NULL)
	{
		*curpath = ft_strdup(ft_child_search_myenv(myenv, "OLDPWD")
				+ ft_strlen("OLDPWD="));
		if (*curpath == NULL)
			return (ft_builtin_errormessage("cd", strerror(errno)));
	}
	else
		return (ft_builtin_errormessage("cd", "OLDPWD not set"));
	return (EXIT_SUCCESS);
}

static int	static_ft_determine_procedure(char *arg, char **myenv,
	char **curpath)
{
	if (arg == NULL && ft_child_search_myenv(myenv, "HOME") == NULL)
		return (ft_builtin_errormessage("cd", "HOME not set"));
	else if (arg == NULL && ft_child_search_myenv(myenv, "HOME") != NULL)
	{
		*curpath = ft_strdup(ft_child_search_myenv(myenv, "HOME")
				+ ft_strlen("HOME="));
		if (*curpath == NULL)
			return (ft_builtin_errormessage("cd", strerror(errno)));
	}
	else if (!ft_strcmp_n(arg, "-", 2))
	{
		if (static_ft_handle_cd_oldpwd(myenv, curpath))
			return (EXIT_FAILURE);
	}
	else
	{
		if (ft_construct_dir(curpath, arg))
			return (ft_builtin_errormessage("cd", strerror(errno)));
	}
	return (EXIT_SUCCESS);
}

int	builtin_cd(char ***myenv, char **args)
{
	char	*curpath;
	int		i;
	int		ret;

	curpath = NULL;
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 2)
		return (ft_builtin_errormessage("cd", "too many arguments"));
	if (static_ft_determine_procedure(args[1], *myenv, &curpath))
	{
		free (curpath);
		return (EXIT_FAILURE);
	}
	ret = static_ft_change_dir(myenv, curpath, args[1]);
	free (curpath);
	curpath = NULL;
	if (ret == ERROR)
		ret = ft_builtin_errormessage("cd", strerror(errno));
	return (ret);
}
