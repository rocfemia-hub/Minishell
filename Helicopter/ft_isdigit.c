/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:10:48 by rocfemia          #+#    #+#             */
/*   Updated: 2024/09/20 11:22:17 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	int	i;

	i = 0;
	if (c >= 48 && c <= 57)
		i = 1;
	else
		i = 0;
	return (i);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isdigit('7'));
}*/