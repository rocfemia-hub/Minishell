/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:21:23 by roo              ###   ########.fr       */
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
    new_arg = ft_calloc(j + 1, sizeof(char *));
    if (!new_arg)
        return(NULL);
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
    realloc_matrix = ft_calloc(j + 2, sizeof(char *));
    if(!realloc_matrix)
        return(NULL);
    j = -1;
    while (flag[++j])
        realloc_matrix[j] = ft_strdup(flag[j]);
    return(realloc_matrix);
}

void fill(t_com *commands, int start, int end, char *redirect, char *file)
{ // dejar solo arg en args y rellenar flags, poner los archivos
    char **new_arg;
 
    new_arg = copy_redirect_matrix(commands->args, start, end); // copia los args sin las lineas del simbolo y file
    commands->args = new_arg;
    if (ft_strncmp(redirect, "<", 2) == 0) 
    {
        if (!commands->redirects->input_file) //me crea el char ** de la estructura si no esta creado
            commands->redirects->input_file = ft_calloc(2, sizeof(char *));
        else //me realoca la memoria del char ** para poder añadir otra linea de file
            commands->redirects->input_file = realloc_redirect_flags(commands->redirects->input_file);
        commands->redirects->input_file[commands->redirects->redirect_in] = ft_strdup(file);
        commands->redirects->redirect_in++;
    }
    else if (ft_strncmp(redirect, ">", 2) == 0)
    {
        if (!commands->redirects->output_file) //me crea el char ** de la estructura si no esta creado
            commands->redirects->output_file = ft_calloc(2, sizeof(char *));
        else //me realoca la memoria del char ** para poder añadir otra linea de file
            commands->redirects->output_file = realloc_redirect_flags(commands->redirects->output_file);
        commands->redirects->output_file[commands->redirects->redirect_out] = ft_strdup(file);
        commands->redirects->redirect_out++;
    }
    else if (ft_strncmp(redirect, "<<", 2) == 0) // falta poner la ultima palabra
    {
        commands->redirects->delimiter = ft_strdup(file);
        commands->redirects->redirect_heredoc = 1;
    }
    else if (ft_strncmp(redirect, ">>", 2) == 0)
    {
        if(!commands->redirects->append_file) //me crea el char ** de la estructura si no esta creado
            commands->redirects->append_file = ft_calloc(2, sizeof(char *));
        else //me realoca la memoria del char ** para poder añadir otra linea de file
            commands->redirects->append_file = realloc_redirect_flags(commands->redirects->append_file);
        commands->redirects->append_file[commands->redirects->redirect_append] = ft_strdup(file);
        commands->redirects->redirect_append++;
    }
    free(file);
}

int parser_redirects(t_com *commands, char *redirect)
{ // chequear si despues de la redireccion hay archivo o antes 
    char *file = NULL; // archivo de salida

    if (ft_strnstr(commands->args[commands->redirects->j], ">>>", 3)) // error >>>
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
        return (0);
    }
    else if (commands->args[commands->redirects->j][0] != redirect[0] || ft_strnstr(commands->args[commands->redirects->j], "<<<", 3)) // error hola< y <<<
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
        return (0);
    }
    else if (ft_strlen(commands->args[commands->redirects->j]) > ft_strlen(redirect))// si la redireccion esta asi ">adios" --> no es error
    {
        file = ft_strdup(commands->args[commands->redirects->j] + ft_strlen(redirect)); // archivo al que redirecciona
        fill(commands, commands->redirects->j, commands->redirects->j, redirect, file); // rellena estructura
    }
    else // el archivo esta separado del simbolo "hola > adios"
    {
        if (!commands->args[commands->redirects->j + 1]) // no hay archivo al que redireccionar
        {
            commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
            return(0);
        }
        if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1) || ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1)) // dos operadores juntos > >
        {
            if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1))
                commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
            if (ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1))
                commands->error = ft_strdup("bash: syntax error near unexpected token `<'");
            return(0);
        }
        file = ft_strdup(commands->args[commands->redirects->j + 1]); //archivo al que redirecciona
        fill(commands, commands->redirects->j, commands->redirects->j+1, redirect, file); // rellena estructura
    }
    return(1);
}

void find(t_com *commands)
{ // look for < or >
    while (commands->args && commands->args[commands->redirects->j])
    {
        if (ft_strnstr(commands->args[commands->redirects->j], ">>", ft_strlen(commands->args[commands->redirects->j])))
        {
            if (!parser_redirects(commands, ">>")) //pasa el tipo se redireccion encontrada
                return ;
            commands->redirects->j = -1;
        }
        else if (ft_strnstr(commands->args[commands->redirects->j], "<<", ft_strlen(commands->args[commands->redirects->j])))
        {
            if(!parser_redirects(commands, "<<"))
                return ;
            commands->redirects->j = -1;
        }
        else if (ft_strnstr(commands->args[commands->redirects->j], ">", ft_strlen(commands->args[commands->redirects->j])))
        {
            if (!parser_redirects(commands, ">"))
                return ;
            commands->redirects->j = -1;
        }
        else if (ft_strnstr(commands->args[commands->redirects->j], "<", ft_strlen(commands->args[commands->redirects->j])))
        {
            if (!parser_redirects(commands, "<"))
                return ;
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
