/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:46 by roo               #+#    #+#             */
/*   Updated: 2025/10/08 13:19:45 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_com *lstnew(int index) // he borrado el new->fd_out = 1; porque lo he declarado en otra función y hacía q la min explotara
{
	t_com *new;

	new = (t_com *)ft_calloc(sizeof(t_com), 1);
	if (!new)
		return (NULL);
	new->index = index;
	return (new);
}

void lstadd_back(t_com **lst, t_com *new)
{
	t_com *node;

	if (!lst || !new)
		return;
	node = *lst;
	if (!node)
	{
		*lst = new;
		return;
	}
	while (node->next)
		node = node->next;
	node->next = new;
	new->previous = node;
}

void print_list(t_com *list)
{ // funcion para debuguear
	while (list)
	{
		int i = 0;
		printf("Index: %d, ", list->index);
		if (list->command)
			printf("command: %s, ", list->command);
		else
			printf("command: (null), ");
		if (list->args)
		{
			while (list->args && list->args[i])
			{
				printf("argumentos: %s\n", list->args[i]);
				i++;
			}
		}
		else
			printf("argumentos: (null)\n");
		if (list->command_arg)
		{
			printf("command_arg\n");
			//printf_matrix (list->command_arg);
		}
		else
			printf("command_arg: (null)\n");
		// if (list->flag_built)
		// 	printf("flag_built: %d\n", list->flag_built);
		// else
		// 	printf("flag_built: (null)\n");
		// printf("\033[34mprint_redirects:\033[0m\n");
		// printf("append_file: %s, flag: %d\n", list->redirects->append_file[0], list->redirects->redirect_append);
		// printf("input_file: %s, flag: %d\n", list->redirects->input_file[0], list->redirects->redirect_in);
		// printf("output_file: %s, flag: %d\n", list->redirects->output_file[0], list->redirects->redirect_out);
		// printf("output_file: %s, flag: %d\n", commands->redirects->output_file[1], commands->redirects->redirect_out);
		list = list->next;
	}
}
