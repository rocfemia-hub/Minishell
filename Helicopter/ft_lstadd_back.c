/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:53:24 by roo               #+#    #+#             */
/*   Updated: 2025/03/16 15:03:59 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

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
/*#include <stdio.h>
int main() 
{
    t_list *myList;
	myList = NULL;
	
    t_list *element1 = ft_lstnew("Element 1");
    t_list *element2 = ft_lstnew("Element 2");
    t_list *element3 = ft_lstnew("Element 3");

    ft_lstadd_back(&myList, element1);
    ft_lstadd_back(&myList, element2);
    ft_lstadd_back(&myList, element3);

    while (myList) 
    {
        printf("%s\n", (char *)(myList->content));
        myList = myList->next;
    }
	
    return (0);
}*/