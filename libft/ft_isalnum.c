/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:10:28 by rocfemia          #+#    #+#             */
/*   Updated: 2024/09/20 11:22:25 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	i;

	i = 0;
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		i = 1;
	else if (c >= 48 && c <= 57)
		i = 1;
	else
		i = 0;
	return (i);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isalnum('-'));
}*/