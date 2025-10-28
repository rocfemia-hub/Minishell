/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:46 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:36:48 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **realloc_redirect_flags(char **flag)
{ // extender los char ** en caso de haber mas de 1 redireccion
    int j;
    char **realloc_matrix;

    j = 0;
    while (flag[j])
        j++;
    realloc_matrix = ft_calloc(j + 2, sizeof(char *));
    if (!realloc_matrix)
        return (NULL);
    j = -1;
    while (flag[++j])
        realloc_matrix[j] = ft_strdup(flag[j]);
    ft_free_free(flag);
    return (realloc_matrix);
}

char **copy_redirect_matrix(char **args, int start, int end)
{ // copiar matriz de args sin el simbolo de redireccion y el nombre del archivo
    int i;
    int j;
    char **new_arg;

    i = 0;
    j = 0;
    while (args[j])
        j++;
    new_arg = ft_calloc(j + 1, sizeof(char *));
    if (!new_arg)
        return (NULL);
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
    return (new_arg);
}

void handle_redirect_array(char ***arr, int *flag, char *file)
{ // triple puntero para modificar el valor fuera de la funcion local
    if (!*arr)
        *arr = ft_calloc(2, sizeof(char *));
    else
        *arr = realloc_redirect_flags(*arr); // me hace un espacio de memoria mas para añadir la nuvea redireccion
    (*arr)[*flag] = ft_strdup(file);         // me mete en el ultimo la redireccion
    (*flag)++;                               // flag que si es mayor a 1 es que hay ese tipo de redireccion
}

void fill_type_redirect(t_com *commands, int type)
{
    int *temp;
    int i;
    int size;

    temp = commands->redirects->type_redirec;
    if (!temp)
    {
        commands->redirects->type_redirec = ft_calloc(2, sizeof(int));
        commands->redirects->type_redirec[0] = type;
    }
    else
    {
        size = 0;
        while (temp[size] != 0)
            size++;
        commands->redirects->type_redirec = ft_calloc(size + 2, sizeof(int));
        i = -1;
        while (++i < size)
            commands->redirects->type_redirec[i] = temp[i];
        commands->redirects->type_redirec[size] = type;
        free(temp);
    }
}

void fill(t_com *commands, int start, int end, char *redirect)
{
    commands->args = copy_redirect_matrix(commands->args, start, end);
    if (ft_strncmp(redirect, "<", 2) == 0)
        handle_redirect_array(&commands->redirects->input_file, &commands->redirects->redirect_in, commands->redirects->file);
    else if (ft_strncmp(redirect, ">", 2) == 0)
        handle_redirect_array(&commands->redirects->output_file, &commands->redirects->redirect_out, commands->redirects->file);
    else if (ft_strncmp(redirect, ">>", 3) == 0)
        handle_redirect_array(&commands->redirects->append_file, &commands->redirects->redirect_append, commands->redirects->file);
    else if (ft_strncmp(redirect, "<<", 3) == 0)
    {
        commands->redirects->delimiter = ft_strdup(commands->redirects->file);
        commands->redirects->redirect_heredoc = 1;
    }
    free(commands->redirects->file);
}
