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

void print_stack(t_com *stack)
{
	while (stack)
	{
		printf("Index: %d, command: %s\n, command_arg: %s\n", stack->index, stack->command, stack->command_arg);
		stack = stack->next;
	}
}
