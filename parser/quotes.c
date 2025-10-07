/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:20:36 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **realloc_quotes_arg(char **args, int i)
{
    int j;
    char **aux;
    int k;

    j = 0;
    k = 0;
    while(args[j])
        j++;
    aux = ft_calloc(j, sizeof(char *));
    j = 0;
    while(args[j])
    {
        if (j == i)
            j++;
        else
        {
            aux[k] = ft_strdup(args[j]);
            k++;
            j++;
        }
    }
    aux[k] = '\0';
    ft_free_free(args);
    return(aux);
}


void keep_quotes_args(t_com *commands, char *line)
{ // split args but KEEP quotes
    int i = 0;
    int j = 0;
    int start;
    char **args = ft_calloc(sizeof(char *), (ft_strlen(line) + 1));

    if (!args)
        return ;
    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        if (!line[i])
            break;
        start = i;
        if (line[i] == '\'' || line[i] == '"')
        {
            char quote = line[i++];
            while (line[i] && line[i] != quote)
                i++;
            if (line[i] == quote)
                i++;
        }
        else
        {
            while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '"')
                i++;
        }
        args[j++] = ft_substr(line, start, i - start); // <-- incluye las comillas
    }
    args[j] = NULL;
    commands->args = args;
    if (!commands->args)
        ft_free_free(commands->args);
    printf_matrix(args);
}

void clean_quotes_in_args(t_com *commands)
{ //clean quotes of char **args
    int i = 0;
    int j, k;
    char *arg;
    char *new_arg;
    char quote;

    while (commands->args && commands->args[i])
    {
        arg = commands->args[i];
        new_arg = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
        if (!new_arg)
            return ;
        j = 0;
        k = 0;
        quote = 0;
        while (arg[j])
        {
            if ((arg[j] == '\'' || arg[j] == '"'))
            {
                if (!quote)              // abrir comilla
                    quote = arg[j];
                else if (quote == arg[j]) // cerrar comilla
                    quote = 0;
                else
                    new_arg[k++] = arg[j]; // comilla distinta → carácter normal
            }
            else
                new_arg[k++] = arg[j];
            j++;
        }
        new_arg[k] = '\0';
        free(commands->args[i]);
        commands->args[i] = new_arg;
        i++;
    }
}

char *clean_cmd(char *line, t_clean_cmd *data)
{ // clean quotes of command
    while (line[data->i] == ' ' || line[data->i] == '\n')
        data->i++;
    if (line[data->i] == '\'' || line[data->i] == '"')
    {
        data->quote = line[data->i]; 
        data->i++;
        data->start = data->i;
        while (line[data->i] && line[data->i] != data->quote)
            data->i++;
        data->end = data->i;
        data->end_index = data->i + 1;
        return (ft_substr(line, data->start, data->end - data->start));
    }
    data->start = data->i;
    while (line[data->i] && line[data->i] != ' ')
        data->i++;
    data->end = data->i;
    data->end_index = data->end;
    return (ft_substr(line, data->start, data->end - data->start));
}

int look_for_char(char *line, char c)
{  // buscar un caracter que no este dentro de comillas y devuelve las veces encontrado
    int i;
    int count;
    char open_quote;

    i = 0;
    count = 0;
    open_quote = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!open_quote) //open
                open_quote = line[i]; 
            else if (line[i] == open_quote) //close
                open_quote = 0; 
        }
        else if (line[i] == c && !open_quote)
            count++; 
        i++;
    }
    if (open_quote != 0)
        return (-1); // error
    return (count);
}
