/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:46 by roo               #+#    #+#             */
/*   Updated: 2025/11/11 18:41:53 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_com	*lstnew(int index)
{
	t_com	*new;

	new = (t_com *)ft_calloc(sizeof(t_com), 1);
	if (!new)
		return (NULL);
	new->vars = NULL;
	new->index = index;
	return (new);
}

void	lstadd_back(t_com **lst, t_com *new)
{
	t_com	*node;

	if (!lst || !new)
		return ;
	node = *lst;
	if (!node)
	{
		*lst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
	new->previous = node;
}
