/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:58:04 by rocfemia          #+#    #+#             */
/*   Updated: 2024/10/04 16:07:58 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*o;
	unsigned char		ch;

	o = (const unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (o[i] == ch)
		{
			return ((void *)&o[i]);
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%s\n", (char *) ft_memchr("picota", 'c', 6));
	return (0);
}*/