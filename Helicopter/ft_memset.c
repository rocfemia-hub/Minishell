/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:10:58 by rocfemia          #+#    #+#             */
/*   Updated: 2024/10/12 15:59:42 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>
int	main(void)
{
	char str[8] = "patatita";
	printf("%s\n", str);
	ft_memset(str, '*', 4);
	//ft_memset(str+4, '*', 4);
	printf("%s\n", str);
	return (0);
}*/
//todo lo que cambias en el ptr tabén se cambia en la s porque no está
//haciendo una copia, esta está apuntando a esa dirección de memoria.