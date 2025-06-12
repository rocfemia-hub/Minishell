/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:29:42 by rocfemia          #+#    #+#             */
/*   Updated: 2024/10/04 12:31:43 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str1[8] = "Patatizo";
	char str2[6] = "Picota";
	printf("%s\n", (char *)ft_memcpy(str1, str2, 14));
	char str3[8] = "Patatizo";
	char str4[6] = "Picota";
	printf("%s\n", (char *)memcpy(str3, str4, 14));
	return (0);
}*/