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

void print_list(t_com *list)
{ // funcion para debuguear
    while (list)
    {
        printf("Index: %d, ", list->index);

        if (list->command && list->command)
            printf("command: %s, ", list->command);
        else
            printf("command: (null), ");

        if (list->arg && list->arg)
            printf("argumentos: %s\n", list->arg);
        else
            printf("argumentos: (null)\n");

        list = list->next;
    }
}
