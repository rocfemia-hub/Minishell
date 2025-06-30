#include "../minishell.h"

t_com *lstnew(int index)
{
	t_com *new;

	new = (t_com *)malloc(sizeof(t_com));
	if (!new)
		return (NULL);
	new->previous = NULL;
	new->index = index;
	new->fd_out = 1;
	new->command = NULL;
	new->arg = NULL;
	new->command_arg = NULL;
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
