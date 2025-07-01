/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:38:48 by roo               #+#    #+#             */
/*   Updated: 2025/03/16 14:58:59 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*#include <stdio.h>
int main() 
{
    t_list *list;
    
	list = NULL;
    ft_lstadd_back(&list, ft_lstnew("Element 1"));
    ft_lstadd_back(&list, ft_lstnew("Element 2"));
    ft_lstadd_back(&list, ft_lstnew("Element 3"));

    int size = ft_lstsize(list);
    printf("List size: %d\n", size);

    return (0);
}*/