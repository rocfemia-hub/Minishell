/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:34 by roo               #+#    #+#             */
/*   Updated: 2025/11/07 20:24:54 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(t_com *commands)
{
	ft_printf(2, "minishell: syntax error\n");
	free_t_com_list(commands);
	return ;
}

// void printf_matrix(char **split)
// {
//     int i = 0;

//     if (!split)
//         return;
//     while (split[i])
//     {
//         printf("->%s\n", split[i]);
//         i++;
//     }
// }