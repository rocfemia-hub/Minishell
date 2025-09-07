/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/09/07 17:11:02 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **copy_redirect_matrix(char **args, int start, int end)
{ //copiar matriz de args sin el simbolo de redireccion y el nombre del archivo
    int i;
    int j;
    char **new_arg;

    i = 0;
    j = 0;
    while (args[j])
        j++;
    new_arg = calloc(j + 1, sizeof(char *));
    j = 0;
    while (args[j])
    {
        if (j < start || j > end)
        {
            new_arg[i] = ft_strdup(args[j]);
            i++;
        }
        j++;
    }
    return(new_arg);
}

void fill(t_com *commands, int start, int end, char *redirect)
{ // dejar solo arg en args y rellenar flags
    char **new_arg;

    new_arg = copy_redirect_matrix(commands->args, start, end);
    ft_free_free(commands->args);
    commands->args = new_arg;

    if (ft_strncmp(redirect, "<", 2) == 0)
        commands->redirects->redirect_in = 1;
    else if (ft_strncmp(redirect, ">", 2) == 0)
        commands->redirects->redirect_out = 1;
    else if (ft_strncmp(redirect, "<<", 2) == 0 || ft_strncmp(redirect, ">>", 2) == 0)
        commands->redirects->redirect_append = 1;
}

void parser_redirects(t_com *commands, char *redirect)
{ // chequear si despues de la redireccion hay archivo o antes 
    char *file = NULL; // archivo de salida, no se si es > >> < <<

    if (commands->args[commands->redirects->j][0] != redirect[0] || (ft_strlen(commands->args[commands->redirects->j]) > ft_strlen(redirect) &&
        (commands->args[commands->redirects->j][ft_strlen(redirect)] == '>' || commands->args[commands->redirects->j][ft_strlen(redirect)] == '<'))) // hola< que de error y <<< <> de error
    {
        commands->redirects->sintax_error = 1;
        return;
    }
    if (ft_strlen(commands->args[commands->redirects->j]) > ft_strlen(redirect))// si la redireccion esta asi ">adios"
    {
        file = ft_strdup(commands->args[commands->redirects->j] + ft_strlen(redirect));
        fill(commands, commands->redirects->j, commands->redirects->j, redirect);
    }
    else // el archivo esta en la siguiente linea
    {
        if (!commands->args[commands->redirects->j + 1]) 
        {
            commands->redirects->error = 1;
            return;
        }
        if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1) || ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1)) // dos operadores juntos > >
        {
            commands->redirects->sintax_error = 1;
            return;
        }
        file = ft_strdup(commands->args[commands->redirects->j + 1]);
        fill(commands, commands->redirects->j, commands->redirects->j+1, redirect);
    }
}

void find(t_com *commands)
{ // look for < or >
    while (commands->args[commands->redirects->j])
    {
        if (ft_strnstr(commands->args[commands->redirects->j], ">>", ft_strlen(commands->args[commands->redirects->j])))
            parser_redirects(commands, ">>"); //pasa el tipo se redireccion encontrada
        else if (ft_strnstr(commands->args[commands->redirects->j], "<<", ft_strlen(commands->args[commands->redirects->j])))
            parser_redirects(commands, "<<");
        else if (ft_strnstr(commands->args[commands->redirects->j], ">", ft_strlen(commands->args[commands->redirects->j])))
            parser_redirects(commands, ">");
        else if (ft_strnstr(commands->args[commands->redirects->j], "<", ft_strlen(commands->args[commands->redirects->j])))
            parser_redirects(commands, "<");

        commands->redirects->j++;
    }
}

void redirects(t_com *commands)
{
    commands->redirects = ft_calloc(2, sizeof(t_red)); // redirect struct
    find(commands); 
}
