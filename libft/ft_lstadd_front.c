/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:08:04 by roo               #+#    #+#             */
/*   Updated: 2025/03/16 15:09:58 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst | !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*#include <stdio.h>
int main() 
{
    t_list *myList;
	myList = NULL;

    t_list *element1 = ft_lstnew("Patata");
    t_list *element2 = ft_lstnew("Aguacate");
    t_list *element3 = ft_lstnew("Limones");

    ft_lstadd_front(&myList, element3);
    ft_lstadd_front(&myList, element2);
    ft_lstadd_front(&myList, element1);

    while (myList) 
    {
        printf("%s\n", (char *)(myList->content));
        myList = myList->next;
    }

    return 0;
}*/