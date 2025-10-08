/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:04 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 16:54:39 by roo              ###   ########.fr       */
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
    data->quote = 0;
    if (!line[data->only_cmd_i])
        return (NULL);
    while (line[data->only_cmd_i] == 32 || line[data->only_cmd_i] == '\n')
        data->only_cmd_i++;
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

    ft_bzero(&data, sizeof(t_clean_cmd));
    data.cmd = only_cmd(line, &data);
    len_cmd = ft_strlen(data.cmd) + 1;
    if (ft_strnstr(data.cmd, "$", ft_strlen(data.cmd)))
    {
        expand_cmd(&data); // si hay $ en el comando, lo expande sea valido o no
        if (data.cmd)      // si la expansion del comando es vacio, como lo siguiente como comando
        {
            data.cmd = only_cmd(line, &data);
            data.cmd = clean_cmd(data.cmd, &data);                 //  limpia el comando de comillas
            init_struct(line, data.cmd, data.end_index + len_cmd, commands); // introduce todo en la estructura
        }
    }
    else
    {
        data.cmd = clean_cmd(line, &data);                 //  limpia el comando de comillas
        init_struct(line, data.cmd, data.end_index, commands); // introduce todo en la estructura
    }
    free(data.cmd);                                        // LIBERAR TODO DATA
}

void init_commands(char *line, t_com *commands)
{
    int i = 0;
    int start = 0;
    char quote = 0;
    t_com *current = commands;

    while (line[i])
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
        i++;
    }
    if (current)
        type_command(line + start, current);
}

t_com *token(char *line)
{
    t_com *commands;

    commands = create_struct(line);
    if (commands->error)
    {
        error(commands);
        return (NULL);
    }
    if (look_for_char(line, 92) || look_for_char(line, 59))
    {
        if (look_for_char(line, 92))
            commands->error = ft_strdup("bash: syntax error backslash");
        if (look_for_char(line, 59))
            commands->error = ft_strdup("bash: syntax error semicolon");
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
