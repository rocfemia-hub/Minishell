/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:00 by rocfemia          #+#    #+#             */
/*   Updated: 2024/10/12 08:00:12 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sig;
	long	result;

	i = 0;
	sig = 1;
	result = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sig = sig * -1;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		if (result * sig > INT_MAX)
			return (-1);
		if (result * sig < INT_MIN)
			return (0);
		i++;
	}
	return (result * sig);
}
/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	result1;
	int	result2;
	result1 = ft_atoi("9999999999999999999999999999999999999999999999999999999");
	printf("%i\n", result1);
	result2 = atoi("9999999999999999999999999999999999999999999999999999999");
	printf("%i\n", result2);
}*/