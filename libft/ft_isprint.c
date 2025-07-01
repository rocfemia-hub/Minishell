/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:10:50 by rocfemia          #+#    #+#             */
/*   Updated: 2024/09/20 11:22:41 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	int	i;

	i = 0;
	if (c >= 32 && c <= 126)
		i = 1;
	else
		i = 0;
	return (i);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isprint('f'));
}*/