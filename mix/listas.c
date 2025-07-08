#include "../minishell.h"

t_com *lstnew(int index)
{
	t_com *new;

	new = (t_com *)malloc(sizeof(t_com));
	if (!new)
		return (NULL);
	new->previous = NULL;
	new->index = index;
	new->command = NULL;
	new->arg = NULL;
	new->command_arg = NULL;
	new->path_command = NULL; // anadiendo la inicialización de pah_command
	new->flag_built = 0;
	new->next = NULL;
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

void free_list(t_com *list)
{
	t_com *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		// he añadido muchos más frees para liberar todas las strings de la lista
		if (temp->command)
            free(temp->command);
        if (temp->arg)
            free(temp->arg);
        if (temp->command_arg)
            free(temp->command_arg);
        if (temp->path_command)
            free(temp->path_command);
		free(temp);
	}
}

void print_list(t_com *list) // funcion para debuguear
{
	while (list)
	{
		printf("Index: %d, command: %s\n, command_arg: %s\n", list->index, list->command, list->command_arg);
		list = list->next;
	}
}