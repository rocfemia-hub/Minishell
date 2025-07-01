/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:45:03 by rocfemia          #+#    #+#             */
/*   Updated: 2024/10/12 16:23:07 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char *s1;
	char *s2;
	
	s1 = strdup("Picota");
	s2 = strdup("Patata");
	printf("%zu\n", ft_strlcpy(s1, s2, 7));
	printf("%s\n", s1);
	free(s1);
	free(s2);
	return(0);
}*/