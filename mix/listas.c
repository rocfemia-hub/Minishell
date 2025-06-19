#include "../minishell.h"

t_com *lstnew(void *content)
{
	t_com	*new;

	new = (t_com *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->command = content;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_com **lst, t_com *new)
{
	t_com	*node;

	node = *lst;
	if (!node)
	{
		*lst = new;
		return ;
	}
	while (lst && node->next != NULL)
	{
		node = node->next;
	}
	node->next = new;
}