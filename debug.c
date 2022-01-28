#include "minishell.h"

void	ft_print_tokenlist(t_slist	**tokens)
{
	t_slist	*ptr;
	int		i;

	printf("tokenlist:\n");
	ptr = *tokens;
	i = 0;
	while (ptr != NULL)
	{
		printf("token %d: %s|\n", i, (char *)ptr->content);
		ptr = ptr->next;
		i++;
	}
}

void	ft_print_tokenarray(char **tokens)
{
	int	i;

	printf("tokenarray:\n");
	i = 0;
	while (tokens[i] != NULL)
	{
		printf("token %d: %s|\n", i, tokens[i]);
		i++;
	}
}

void	ft_print_data(t_data *data)
{
	t_slist	*commandlist;
	int		i;
	t_re	*tmp;

	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	commandlist = data->commands;
	while (commandlist != NULL)
	{
		printf(".....................................................................\n");
		printf("path: %s\n", ((t_cmd *)commandlist->content)->path);
		i = 0;
		while (((t_cmd *)commandlist->content)->args[i] != NULL)
		{
			printf("arg[%d]: %s|\n", i, ((t_cmd *)commandlist->content)->args[i]);
			i++;
		}
		tmp = ((t_cmd *)commandlist->content)->re;
		while (tmp != NULL)
		{
			printf("operator: %d file: %s\n", tmp->operator, tmp->file);
			tmp = tmp->next;
		}
		printf("fd[0]: %d fd[1]: %d\n", ((t_cmd *)commandlist->content)->fd[0], ((t_cmd *)commandlist->content)->fd[1]);
		commandlist = commandlist->next;
		printf(".....................................................................\n");
	}
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<END>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}