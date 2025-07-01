/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 05:33:58 by roo               #+#    #+#             */
/*   Updated: 2024/10/04 15:51:25 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*aux1;
	char	*aux2;

	aux1 = (char *)s1;
	aux2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)aux1[i] > (unsigned char)aux2[i])
			return (1);
		else if ((unsigned char)aux1[i] < (unsigned char)aux2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%i\n", ft_memcmp("Patata", "Patatita", 9));
	printf("%i\n", memcmp("Patata", "Patatita", 9));
	return(0);
}*/