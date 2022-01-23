/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2021/12/22 09:36:47 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_lastpid = 0;

static void	static_ft_copy_environ(t_data *data)
{
	extern char	**environ;
	int			count;

	if (environ != NULL)
	{
		count = 0;
		while (environ[count] != NULL)
			count++;
		data->myenv = malloc((count + 1) * sizeof(char *));
		if (data->myenv == NULL)
			ft_exit_errno(data);
		count = 0;
		while (environ[count] != NULL)
		{
			data->myenv[count] = ft_strdup(environ[count]);
			if (data->myenv[count] == NULL)
				ft_exit_errno(data);
			count++;
		}
		data->myenv[count] = NULL;
	}
	else
		data->myenv = NULL;
}

int	handlecmd(char **command, t_data *data)
{
	char	**temp;

	data->commands = NULL;
	if (ft_expander(command, data))
		ft_exit(data);
	temp = ft_removeq(command);
	data->commands = ft_parser(temp, data);
	if (data->commands == NULL || ft_emptystruct(data->commands, data))
		return (-1);
	data->mypipe[READ] = -1;
	data->mypipe[WRITE] = -1;
	ft_execute(data);
	return (0);
}
//	printf("here comes the command table: \n");
//	ft_printsimplecmd(data->commands);

void	helpermain(char *input, t_data *data)
{
	if (input == NULL)
		builtin_exit(data, NULL);
	if (ft_strlen(input) > 0)
		add_history(input);
}

int	main(void)
{
	char			*input;
	char			**command;
	t_data			data;
	struct termios	termi;

	tcgetattr(STDIN_FILENO, &termi);
	data.lastexitstatus = EXIT_SUCCESS;
	static_ft_copy_environ(&data);
	while (1)
	{
		signal(SIGINT, &sighandler);
		signal(SIGQUIT, SIG_IGN);
		ctrlc(&termi, 0);
		input = readline(PROMPT);
		helpermain(input, &data);
		command = ft_tokenizer(input, &data);
		free(input);
		if (command != NULL)
		{
			if (handlecmd(command, &data) == -1)
				continue ;
		}
	}
	ctrlc(&termi, 1);
	return (EXIT_SUCCESS);
}
