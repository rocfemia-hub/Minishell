/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:14:34 by roo               #+#    #+#             */
/*   Updated: 2024/10/12 13:44:03 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digits(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		n_dig;
	int		flag;
	long	ln;

	ln = n;
	n_dig = ft_digits(ln);
	result = (char *)malloc(n_dig * sizeof(char) + 1);
	if (!result)
		return (NULL);
	result[n_dig--] = '\0';
	flag = 1;
	if (ln < 0)
		flag = -1;
	while (n_dig >= 0)
	{
		result[n_dig] = (ln * flag % 10) + 48;
		ln = ln / 10;
		n_dig--;
	}
	if (flag == -1)
		result[0] = '-';
	return (result);
}
/*#include <stdio.h>
int	main(void)
{
	//printf("%d\n", ft_digits(-180));
	printf("%s\n", ft_itoa(-180)); //return ("-180'\0'")
	return(0);
}*/