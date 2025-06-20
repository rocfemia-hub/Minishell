#include "../minishell.h"

t_com *lstnew(void *index)
{
	t_com *new;

	new = (t_com *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->previous = NULL;
	new->index = index;
	new->next = NULL;
	return (new);
}

void lstadd_back(t_com **lst, t_com *new)
{
	t_com *node;

	if (!lst || !new)
	return;
	if (!node)
	{
		*lst = new;
		return;
	}
	node = *lst;
	while (lst && node->next)
		node = node->next;
	node->next = new;
	node->previous = node;
}
