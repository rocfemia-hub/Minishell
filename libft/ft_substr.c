/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:07:34 by roo               #+#    #+#             */
/*   Updated: 2024/10/12 14:54:55 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ptr = ft_calloc(1, 1), ptr);
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_substr("Pisapapeles", 4, 4));
	return(0);
}*/