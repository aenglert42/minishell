/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_echo_env_exit_pwd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:07:55 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	static_ft_is_flag(char *arg, char c)
{
	int	i;

	if (arg == NULL)
		return (false);
	if (arg[0] != '-')
		return (false);
	if (arg[1] != c)
		return (false);
	i = 2;
	while (arg[i] != '\0')
	{
		if (arg[i] != c)
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(char **args)
{
	int		i;
	int		j;
	int		flag;

	if (*args == NULL)
		return (EXIT_FAILURE);
	i = 1;
	while (static_ft_is_flag(args[i], 'n'))
		i++;
	flag = i;
	while (args[i] != NULL)
	{
		if (i > flag)
			ft_putchar_fd(' ', STDOUT_FILENO);
		j = 0;
		while (args[i][j] != '\0')
		{
			ft_putchar_fd(args[i][j], STDOUT_FILENO);
			j++;
		}
		i++;
	}
	if (!static_ft_is_flag(args[1], 'n'))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	free (pwd);
	pwd = NULL;
	return (EXIT_SUCCESS);
}

//behavior with arguments like pwd (ignore arguments)
int	builtin_env(char **myenv, bool export)
{
	int	i;

	if (myenv == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (myenv[i] != NULL)
	{
		if (export)
			printf("declare -x ");
		printf("%s\n", myenv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_data *data, char **args)
{
	int	ret;

	write(STDERR_FILENO, "exit\n", 5);
	if (args == NULL || args[1] == NULL)
	{
		ft_free_data_struct_content(data);
		exit(data->lastexitstatus);
	}
	if (!ft_isnumber(args[1]))
	{
		ft_printf_stderr("%s: exit: %s: numeric argument required\n",
			SHELL, args[1]);
		ft_free_data_struct_content(data);
		exit(2);
	}
	if (args[2] != NULL)
		return (ft_builtin_errormessage("exit", "too many arguments"));
	ret = ft_atoi(args[1]);
	ft_free_data_struct_content(data);
	exit(ret);
}
