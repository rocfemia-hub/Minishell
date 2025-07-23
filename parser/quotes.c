/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/07/24 01:34:57 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clean_and_fill_arg(t_com *commands, char *line)
{
    int i = 0;
    int j = 0;
    int start;
    char quote = 0;
    char **args = ft_calloc(sizeof(char *), (ft_strlen(line) + 1));

    if (!args)
        return ;
    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        if (!line[i])
            break;
        if (line[i] == '\'' || line[i] == '"')
        {
            quote = line[i++];
            start = i;
            while (line[i] && line[i] != quote)
                i++;
            args[j++] = ft_substr(line, start, i - start);
            if (line[i] == quote)
                i++;
        }
        else
        {
            start = i;
            while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '"')
                i++;
            args[j++] = ft_substr(line, start, i - start);
        }
    }
    args[j] = NULL;
    commands->args = args;
	if(!commands->args)
		ft_free_free(commands->args);
    return ;
}

char *clean_cmd(char *line, t_clean_cmd *data) 
{
    while (line[data->i] == ' ')
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

int pipes_counter(char *line)
{  // |, <, >, >>, <<  pipes
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
        else if (line[i] == '|' && !open_quote)
            count++; 
        i++;
    }
    if (open_quote != 0)
        return (-1); 
    return (count);
}
