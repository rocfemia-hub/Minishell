/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:09:46 by roo               #+#    #+#             */
/*   Updated: 2024/10/10 14:16:30 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*char	ft_toupper_char(unsigned int j, char c)
{
	if (c != '\0')
	{
		if (c >= 97 && c <= 122)
			j = 1;
		if (j == 1)
			c = c - 32;
	}
	return (c);
}
#include <stdio.h>

int main ()
{
	printf("%s\n", ft_strmapi("PatiTos", ft_toupper_char));
	return(0);
}*/
