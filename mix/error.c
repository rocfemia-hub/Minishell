/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:34 by roo               #+#    #+#             */
/*   Updated: 2025/07/24 01:23:35 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_error() //funcion para gestion de error, no esta hecha
{
  
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