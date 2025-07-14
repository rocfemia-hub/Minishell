#include "../minishell.h"

t_com *lstnew(int index)
{
	t_com *new;

	new = (t_com *)malloc(sizeof(t_com));
	if (!new)
		return (NULL);
	new->previous = NULL;
	new->index = index;
	new->cmd_arg = NULL;
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
		if (temp->cmd_arg)
            ft_free_free(temp->cmd_arg);
        if (temp->path_command)
            free(temp->path_command);
		free(temp);
	}
}

void print_list(t_com *list) // funcion para debuguear
{
    while (list)
    {
        printf("Index: %d, ", list->index);

        if (list->cmd_arg && list->cmd_arg[0])
            printf("command: %s, ", list->cmd_arg[0]);
        else
            printf("command: (null), ");

        if (list->cmd_arg && list->cmd_arg[1])
            printf("argumentos: %s\n", list->cmd_arg[1]);
        else
            printf("argumentos: (null)\n");

        list = list->next;
    }
}
