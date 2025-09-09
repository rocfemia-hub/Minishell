/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/09/09 14:37:11 by roo              ###   ########.fr       */
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
    ft_free_free(args);
    return(new_arg);
}

char **realloc_redirect_flags(char **flag)
{ //extender los char ** en caso de haber mas de 1 redireccion
    int i;
    int j;
    char **realloc_matrix;

    i = 0;
    j = 0;
    while (flag[j])
        j++;
    realloc_matrix = calloc(j + 2, sizeof(char *));
    j = -1;
    while (flag[++j])
        realloc_matrix[j] = ft_strdup(flag[j]);
    return(realloc_matrix);
}

void fill(t_com *commands, int start, int end, char *redirect, char *file)
{ // dejar solo arg en args y rellenar flags, poner los archivos
    char **new_arg;
 
    new_arg = copy_redirect_matrix(commands->args, start, end);
    commands->args = new_arg;
    printf("file: %s\n", file);
    printf("%d\n", commands->redirects->redirect_out);
    if (ft_strncmp(redirect, "<", 2) == 0)
    {
        if (!commands->redirects->input_file)
            commands->redirects->input_file = ft_calloc(2, sizeof(char *));
        else
            commands->redirects->input_file = realloc_redirect_flags(commands->redirects->input_file);
        commands->redirects->input_file[commands->redirects->redirect_in] = ft_strdup(file);
        commands->redirects->redirect_in++;
    }
    else if (ft_strncmp(redirect, ">", 2) == 0)
    {
        if (!commands->redirects->output_file)
            commands->redirects->output_file = ft_calloc(2, sizeof(char *));
        else
            commands->redirects->output_file = realloc_redirect_flags(commands->redirects->output_file);
        commands->redirects->output_file[commands->redirects->redirect_out] = ft_strdup(file);
        printf("--> %s\n", commands->redirects->output_file[commands->redirects->redirect_out]);
        commands->redirects->redirect_out++;
    }
    else if (ft_strncmp(redirect, "<<", 2) == 0) // falta poner la ultima palabra
    {
        commands->redirects->redirect_heredoc = 1;
    }
    else if (ft_strncmp(redirect, ">>", 2) == 0)
    {
        if(!commands->redirects->append_file)
            commands->redirects->append_file = ft_calloc(2, sizeof(char *));
        else
            commands->redirects->append_file = realloc_redirect_flags(commands->redirects->append_file);
        commands->redirects->append_file[commands->redirects->redirect_append] = ft_strdup(file);
        commands->redirects->redirect_append++;
    }
    free(file);
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
        fill(commands, commands->redirects->j, commands->redirects->j, redirect, file);
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
        fill(commands, commands->redirects->j, commands->redirects->j+1, redirect, file);
    }
}

void find(t_com *commands)
{ // look for < or >
    while (commands->args[commands->redirects->j]) // PUEDE DAR SEG F SI NO VERIFICAS SI ARGS EXISTE
    {
        if (ft_strnstr(commands->args[commands->redirects->j], ">>", ft_strlen(commands->args[commands->redirects->j])))
        {
            parser_redirects(commands, ">>"); //pasa el tipo se redireccion encontrada
            commands->redirects->j = -1;
        }
        else if (ft_strnstr(commands->args[commands->redirects->j], "<<", ft_strlen(commands->args[commands->redirects->j])))
        {
            parser_redirects(commands, "<<");
            commands->redirects->j = -1;
        }
        else if (ft_strnstr(commands->args[commands->redirects->j], ">", ft_strlen(commands->args[commands->redirects->j])))
        {
            parser_redirects(commands, ">");
            commands->redirects->j = -1;
        }
        else if (ft_strnstr(commands->args[commands->redirects->j], "<", ft_strlen(commands->args[commands->redirects->j])))
        {
            parser_redirects(commands, "<"); 
            commands->redirects->j = -1;
        }
        commands->redirects->j++;
    }
}

void redirects(t_com *commands)
{
    commands->redirects = ft_calloc(2, sizeof(t_red)); // redirect struct
    find(commands); 
}