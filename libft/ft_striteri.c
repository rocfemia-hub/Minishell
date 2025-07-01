/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:00:02 by roo               #+#    #+#             */
/*   Updated: 2024/10/10 14:23:12 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/* void	ft_toupper_string(unsigned int j, char *str)
{
	while (str[j] != '\0')
	{
		if (str[j] >= 97 && str[j] <= 122)
			str[j] = str[j] - 32;
		j++;
	}
}
//char	*ft_toupper_string(unsigned int j, char *str)
//{
//	while (str[j] != '\0')
//	{
//		if (str[j] >= 97 && str[j] <= 122)
//			str[j] = str[j] - 32;
//		j++;
//	}
//	return (str);
//}
#include <stdio.h>
#include <string.h>

int main ()
{
	char *str = strdup("PataTa");
	printf("%s\n", ft_toupper_string(0, str));
	return (0);
}  */