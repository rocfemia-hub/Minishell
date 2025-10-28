/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:46 by roo               #+#    #+#             */
/*   Updated: 2025/10/15 16:10:16 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_com *lstnew(int index) // he borrado el new->fd_out = 1; porque lo he declarado en otra función y hacía q la min explotara
{
	t_com *new;

	new = (t_com *)ft_calloc(sizeof(t_com), 1);
	if (!new)
		return (NULL);
	new->vars = NULL;  // No asignamos vars aquí, se asignará en init_fds
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
		
		// Verificar si redirects existe antes de acceder
		if (list->redirects)
		{
			printf("\033[34mprint_redirects:\033[0m\n");
			
			// Verificar append_file
			if (list->redirects->append_file && list->redirects->append_file[0])
				printf("append_file: %s, flag: %d\n", list->redirects->append_file[0], list->redirects->redirect_append);
			else
				printf("append_file: (null), flag: %d\n", list->redirects->redirect_append);
			
			// Verificar input_file
			if (list->redirects->input_file && list->redirects->input_file[0])
				printf("input_file: %s, flag: %d\n", list->redirects->input_file[0], list->redirects->redirect_in);
			else
				printf("input_file: (null), flag: %d\n", list->redirects->redirect_in);
			
			// Verificar output_file
			if (list->redirects->output_file && list->redirects->output_file[0])
				printf("output_file: %s, flag: %d\n", list->redirects->output_file[0], list->redirects->redirect_out);
			else
				printf("output_file: (null), flag: %d\n", list->redirects->redirect_out);
			
			// Verificar type_redirec
			if (list->redirects->type_redirec)
			{
				int j = 0;
				printf("type_redirec: [");
				while (list->redirects->type_redirec[j] != 0)
				{
					printf("%d", list->redirects->type_redirec[j]);
					if (list->redirects->type_redirec[j + 1] != 0)
						printf(", ");
					j++;
				}
				printf("]\n");
			}
			else
				printf("type_redirec: (null)\n");
		}
		else
		{
			printf("redirects: (null)\n");
		}
		
		list = list->next;
	}
}
