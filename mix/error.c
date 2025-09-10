/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:34 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:16:03 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error(t_com *commands)
{
    printf("%s\n", commands->error);
    free_t_com_list(commands);
    return;
}

void printf_matrix(char **split) // debugueo de la matrix, escribiendola
{
    int i = 0;

    while (split[i])
    {
        printf("%s\n", split[i]);
        i++;
    }
}