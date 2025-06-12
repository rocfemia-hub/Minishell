/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:04:34 by roo               #+#    #+#             */
/*   Updated: 2024/10/04 15:55:26 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= size)
		return (slen + size);
	while (src[i] && dlen + i < size - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
/*#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char *str1 = strdup("Patatita");
	char *str2 = strdup("Rica");
	printf("%zu\n", ft_strlcat(str1, str2, 2));
	printf("%s\n", str1);
	char *str3 = strdup("Patatita");
	char *str4 = strdup("Rica");
	printf("%zu\n", strlcat(str3, str4, 2));
	printf("%s\n", str3);
	return(0);
}*/