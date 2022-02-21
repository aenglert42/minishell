/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_printstuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:10:27 by jzhou             #+#    #+#             */
/*   Updated: 2022/02/21 20:46:31 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
//here you can find all the printing functions 
//used for errorchecking

//this function prints simple t-lists
void	ft_print_slist(t_slist *tokenlst)
{
	t_slist	*temp;

	temp = tokenlst;
	while (temp != NULL)
	{
		printf("%s.\n", (char *)temp->content);
		temp = temp->next;
	}
}
	// if (temp == NULL)
	// printf("%s.\n", (char *)NULL);

//this function prints the command in char ** form
void	ft_printcharcmd(char **command)
{
	int	y;

	y = 0;
	while (command != NULL && command[y] != NULL)
	{
		printf("%s.\n", command[y]);
		y++;
	}
	printf("%s.\n", command[y]);
}

//this function prints a simple node of the cmdtable list

void	ft_printsimplenode(t_cmd *simplecmd)
{
	int		y;
	t_re	*temp1;

	y = 1;
	temp1 = NULL;
	printf("Node: \n");
	printf("path: %s.\n", simplecmd->path);
	printf("command: %s.\n", simplecmd->args[0]);
	while (simplecmd->args[y] != NULL)
	{
		printf("argument: %s. ", simplecmd->args[y]);
		y++;
	}
	printf("\n");
	printf("hasheredoc: %d.\n", simplecmd->hasheredoc);
	printf("isbuiltin: %d.\n", simplecmd->isbuiltin);
	temp1 = simplecmd->re;
	while (temp1 != NULL)
	{
		printf("re-op: %d\n", temp1->operator);
		printf("re-file: %s\n", temp1->file);
		temp1 = temp1->next;
	}
	printf("pid: %d.\n", simplecmd->pid);
	printf("fd: %d.\n", simplecmd->fd[0]);
	PRINT_HERE();
}

//this function prints the command table list of structs
void	ft_printsimplecmd(t_slist *cmdtable)
{
	t_cmd *simplecmd;
	t_re *temp1;
	t_slist *temp2;
	int y;

	temp1 = NULL;
	temp2 = cmdtable;
	while (temp2 != NULL)
	{
		printf("Node: \n");
		simplecmd = (t_cmd *)(temp2->content);
		printf("path: %s.\n", simplecmd->path);
		printf("command: %s.\n", simplecmd->args[0]);
		y = 1;
		while (simplecmd->args != NULL && simplecmd->args[y] != NULL)
		{
			printf("argument: %s. ", simplecmd->args[y]);
			y++;
		}
		printf("\n");
		printf("hasheredoc: %d.\n", simplecmd->hasheredoc);
		printf("isbuiltin: %d.\n", simplecmd->isbuiltin);

		temp1 = simplecmd->re;
		while (temp1 != NULL)
		{
			printf("re-op: %d\n", temp1->operator);
			printf("re-file: %s\n", temp1->file);
			temp1 = temp1->next;
		}
		printf("pid: %d.\n", simplecmd->pid);
		printf("fd[0]: %d.\n", simplecmd->fd[0]);
		printf("fd[1]: %d.\n", simplecmd->fd[1]);
		temp2 = temp2->next;
		PRINT_HERE();
	}
}
*/