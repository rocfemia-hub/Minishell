/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:34 by roo               #+#    #+#             */
/*   Updated: 2025/10/08 13:19:10 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error(t_com *commands)
{
    printf("%d: %s\n",commands->vars->exit_error, commands->error);
    free_t_com_list(commands);
    return;
}

// void printf_matrix(char **split) // debugueo de la matrix, escribiendola
// {
//     int i = 0;

//     while (split[i])
//     {
//         printf("->%s\n", split[i]);
//         i++;
//     }
// }