/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:54:56 by roo               #+#    #+#             */
/*   Updated: 2025/10/21 22:10:08 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversions(int fd, va_list vargs, int i, int result)
{
	if (i == 'c')
		result = ft_printf_putchar_fd(va_arg(vargs, int), fd, result);
	else if (i == 's')
		result = ft_printf_putstr_fd(va_arg(vargs, char *), fd, result);
	else if (i == 'p')
		result = ft_printf_p(va_arg(vargs, void *), fd, result);
	else if (i == 'i' || i == 'd')
		result = ft_printf_putnbr_fd(va_arg(vargs, int), fd, result);
	else if (i == 'u')
		result = ft_printf_u(va_arg(vargs, unsigned int), fd, result);
	else if (i == 'x')
		result = ft_printf_x(va_arg(vargs, unsigned int), fd, result);
	else if (i == 'X')
		result = ft_printf_super_x(va_arg(vargs, unsigned int), fd, result);
	else if (i == '%')
		result = ft_printf_putchar_fd('%', fd, result);
	return (result);
}

int	ft_printf(int fd, char const *str, ...)
{
	va_list	vargs;
	int		i;
	int		result;

	i = 0;
	result = 0;
	va_start(vargs, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			result = ft_conversions(fd, vargs, str[i], result);
		}
		else
		{
			result = ft_printf_putchar_fd(str[i], fd, result);
		}
		i++;
	}
	va_end(vargs);
	return (result);
}
