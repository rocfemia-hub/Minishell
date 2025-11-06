/* ************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/10/15 14:48:46 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************** */

#include "../minishell.h"

void keep_quotes_args(t_com *commands, char *line)
{
    int i;
    int j;
    int k;
    char **args;
    char *arg;

    i = 0;
    j = 0;
    args = ft_calloc(sizeof(char *), ft_strlen(line) + 1);
    if (!args)
        return;
    while (line[i])
    {
        i += skip_spaces(line + i);
        if (!line[i])
            break;
        arg = ft_calloc(ft_strlen(line) + 3, sizeof(char));
        if (!arg)
            return(ft_free_free(args));
        k = 0;
        while (line[i] && line[i] != ' ')
        {
            if (line[i] == '\'' || line[i] == '"')
            {
                int start = k;
                char q = line[i++];
                while (line[i] && line[i] != q)
                    arg[k++] = line[i++];
                if (line[i] == q)
                    i++;
                if (ft_strchr(arg + start, '>') || ft_strchr(arg + start, '<'))
                {
                    int m = k;
                    while (m > start)
                    {
                        arg[m] = arg[m - 1];
                        m--;
                    }
                    arg[start] = q;
                    arg[k + 1] = q;
                    k += 2;
                }
            }
            else
                arg[k++] = line[i++];
        }
        arg[k] = '\0';
        args[j++] = arg;
    }
    args[j] = NULL;
    commands->args = args;
}

void clean_reinserted_quotes_in_args(t_com *commands)
{
    int   i;
    int   j;
    int   k;
    char  *arg;
    char  *new_arg;
    int   len;

    i = 0;
    while (commands->args && commands->args[i])
    {
        arg = commands->args[i];
        len = ft_strlen(arg);
        new_arg = ft_calloc(len + 1, sizeof(char));
        if (!new_arg)
            return ;
        j = 0;
        k = 0;
        while (arg[j])
        {
            if (arg[j] == '\'' || arg[j] == '"')
            {
                char q = arg[j];
                int  m = j + 1;
                while (arg[m] && arg[m] != q)
                    m++;
                if (arg[m] == q)
                {
                    int has_redir = 0;
                    int t = j + 1;
                    while (t < m)
                    {
                        if (arg[t] == '>' || arg[t] == '<')
                        {
                            has_redir = 1;
                            break;
                        }
                        t++;
                    }
                    if (has_redir)
                    {

                        int u = j + 1;
                        while (u < m)
                            new_arg[k++] = arg[u++];
                        j = m + 1;
                        continue;
                    }
                    new_arg[k++] = arg[j++];
                    while (j <= m)
                        new_arg[k++] = arg[j++];
                    continue;
                }
                new_arg[k++] = arg[j++];
            }
            else
                new_arg[k++] = arg[j++];
        }
        new_arg[k] = '\0';
        free(commands->args[i]);
        commands->args[i] = new_arg;
        i++;
    }
}

char *clean_cmd(char *line)
{
    char *result;
    char *temp;
    int j, k;
    char quote;

    if (ft_strnstr(line, "<", ft_strlen(line)) || ft_strnstr(line, "<<", ft_strlen(line)) || ft_strnstr(line, ">", ft_strlen(line)) || ft_strnstr(line, ">>", ft_strlen(line)))
        return(ft_strdup(line));
    if (!line)
        return (NULL);
    temp = ft_strdup(line);
    if (!temp)
        return (NULL);
    result = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
    if (!result)
        return (free(temp), NULL);
    j = 0;
    k = 0;
    quote = 0;
    while (temp[j])
    {
        if (temp[j] == '\'' || temp[j] == '"')
        {
            if (!quote)
                quote = temp[j++];
            else if (quote == temp[j])
            {
                quote = 0;
                j++;
            }
            else
                result[k++] = temp[j++];
        }
        else
            result[k++] = temp[j++];
    }
    result[k] = '\0';
    free(temp);
    return (result);
}

int look_for_char(char *line, char c)
{
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
            if (!open_quote)
                open_quote = line[i]; 
            else if (line[i] == open_quote)
                open_quote = 0; 
        }
        else if (line[i] == c && !open_quote)
            count++; 
        i++;
    }
    if (open_quote != 0)
        return (-1);
    return (count);
}
