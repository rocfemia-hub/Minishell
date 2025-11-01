/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:04 by roo               #+#    #+#             */
/*   Updated: 2025/10/15 13:11:40 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int skip_spaces(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] == 32)
        i++;
    return (i);
}

char *only_cmd(char *line, t_clean_cmd *data)
{ // ME SEPARA EL COMANDO DE LA LINEA QUE ENTRA POR TERMINAL
    data->only_cmd_i += skip_spaces(&line[data->only_cmd_i]);
    while (line[data->only_cmd_i] == '\n')
        data->only_cmd_i++;
    data->quote = 0;
    if (!line[data->only_cmd_i])
        return (NULL);
    data->start = data->only_cmd_i;
    while (line[data->only_cmd_i])
    {
        if (line[data->only_cmd_i] == '\'' || line[data->only_cmd_i] == '"')
        {
            if (!data->quote)
                data->quote = line[data->only_cmd_i];
            else if (data->quote == line[data->only_cmd_i])
                data->quote = 0;
        }
        if (line[data->only_cmd_i] == ' ' && data->quote == 0)
        {
            data->end = data->only_cmd_i;
            break;
        }
        data->only_cmd_i++;
    }
    if (!line[data->only_cmd_i])
        data->end = data->only_cmd_i;
    return (ft_substr(line, data->start, data->end - data->start));
}

void type_command(char *line, t_com *commands)
{
    t_clean_cmd data;
    int len_cmd;
    char *temp;
    int saved_index;

    ft_bzero(&data, sizeof(t_clean_cmd));
    data.cmd = only_cmd(line, &data);
    if (!data.cmd)
        return;
    saved_index = data.only_cmd_i;  // Guardar el índice correcto de only_cmd
    len_cmd = ft_strlen(data.cmd) + 1;                  // por si luego tengo que coger el siguiente comando, por perder la referencia
    if (ft_strnstr(data.cmd, "$", ft_strlen(data.cmd))) // hay posible expansion en el comando
    {
        if (expand_cmd(&data, commands->vars)) // si hay $ en el comando
            init_struct(line, data.cmd, data.end_index, commands);
        else // si la expansion del comando es vacio, cojo lo siguiente como comando
        {
            free(data.cmd);
            data.cmd = only_cmd(line, &data);
            temp = data.cmd;
            data.cmd = clean_cmd(data.cmd, &data);
            free(temp);
            init_struct(line, data.cmd, data.only_cmd_i, commands);
        }
    }
    else // cuando no hay expansion
    {
        temp = data.cmd;
        data.cmd = clean_cmd(data.cmd, &data);
        free(temp);
        init_struct(line, data.cmd, saved_index, commands);
    }
    free(data.cmd);
}

void init_commands(char *line, t_com *commands)
{
    int i;
    int start;
    char quote;
    t_com *current;

    i = -1;
    start = 0;
    quote = 0;
    current = commands;
    while (line[++i])
    {
        if ((line[i] == '"' || line[i] == '\''))
        {
            if (!quote)
                quote = line[i];
            else if (quote == line[i])
                quote = 0;
        }
        if (line[i] == '|' && !quote)
        {
            line[i] = '\0';
            type_command(line + start, current);
            start = i + 1;
            current = current->next;
        }
    }
    if (current)
        type_command(line + start, current);
}

t_com *token(char *line, t_vars *vars)
{
    t_com *commands;

    commands = create_struct(line, vars);
    commands->vars = vars;
    if (commands->error)
    {
        error(commands);
        return (NULL);
    }
    init_commands(line, commands);
    if (commands->error)
    {
        error(commands);
        return (NULL);
    }
    return (commands);
}
