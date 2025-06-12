/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:38:13 by roo               #+#    #+#             */
/*   Updated: 2025/01/21 19:40:01 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_x(unsigned long long n, int fd, int result)
{
	if (n >= 16)
	{
		result = ft_printf_x((n / 16), 1, result);
		result = ft_printf_x((n % 16), 1, result);
	}
	else
	{
		if (n < 10)
		{
			n = n + 48;
		}
		else if (n > 9)
		{
			n = n + 87;
		}
		result = ft_printf_putchar_fd(n, fd, result);
	}
	return (result);
}

int	ft_printf_super_x(unsigned int n, int fd, int result)
{
	if (n >= 16)
	{
		result = ft_printf_super_x((n / 16), 1, result);
		result = ft_printf_super_x((n % 16), 1, result);
	}
	else
	{
		if (n < 10)
		{
			n = n + 48;
		}
		else if (n > 9)
		{
			n = n + 55;
		}
		result = ft_printf_putchar_fd(n, fd, result);
	}
	return (result);
}

int	ft_printf_u(unsigned int n, int fd, int result)
{
	if (n > 9)
	{
		result = ft_printf_u((n / 10), 1, result);
		result = ft_printf_u((n % 10), 1, result);
	}
	else
		result = ft_printf_putchar_fd((n + '0'), fd, result);
	return (result);
}

int	ft_printf_p(void *p, int fd, int result)
{
	unsigned long long	i;

	i = (unsigned long long)p;
	if (i == 0)
	{
		result = ft_printf_putstr_fd("(nil)", fd, result);
		return (result);
	}
	result = ft_printf_putstr_fd("0x", fd, result);
	result = ft_printf_x(i, fd, result);
	return (result);
}
