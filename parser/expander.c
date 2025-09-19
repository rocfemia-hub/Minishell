/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:34 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:19:11 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *only_cmd(char *line, t_clean_cmd *data)
{  // ME SEPARA EL COMANDO DE LA LINEA QUE ENTRA POR TERMINAL
    int i; 

    i = 0;
    data->quote = 0;
    while (line[i] && line[i] == 32)
        i++;
    if (!line[i])
        return NULL;
    data->start = i;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!data->quote)
                data->quote = line[i];
            else if (data->quote == line[i])
                data->quote = 0;
        }
        if (line[i] == ' ' && data->quote == 0)
        {
            data->end = i;
            break;
        }
        i++;
    }
    if (!line[i])
        data->end = i;
    return (ft_substr(line, data->start, data->end - data->start));
}

char *get_env_var(const char *var)
{
    char *value = getenv(var);
    if (value != NULL)
        return value;
    else
        return "";
}

char *str_append(char *dest, const char *src)
{
    if (!dest)
    {
        dest = strdup(src);
    }
    else
    {
        char *tmp = malloc(strlen(dest) + strlen(src) + 1);
        strcpy(tmp, dest);
        strcat(tmp, src);
        free(dest);
        dest = tmp;
    }
    return dest;
}

char **aux_cmd(t_clean_cmd *data)
{
    char **temp = malloc(sizeof(char *) * 256);
    int i = 0, j = 0, start;
    char quote = 0;

    while (data->cmd[i])
    {
        char *token = NULL;
        if (data->cmd[i] == '\'')
        {
            i++;
            start = i;
            while (data->cmd[i] && data->cmd[i] != '\'')
                i++;
            if (i > start)
            {
                token = ft_substr(data->cmd, start, i - start);
            }
            if (data->cmd[i] == '\'') 
                i++;
        }
        else if (data->cmd[i] == '"')
        {
            i++;
            start = i;
            while (data->cmd[i] && data->cmd[i] != '"')
                i++;
            int end = i;
            int k = start;
            while (k < end)
            {
                if (data->cmd[k] == '$')
                {
                    if (k > start)
                        token = str_append(token, ft_substr(data->cmd, start, k - start));

                    int vstart = k + 1;
                    int vlen = 0;
                    while (data->cmd[vstart + vlen] &&
                           (isalnum((unsigned char)data->cmd[vstart + vlen]) || data->cmd[vstart + vlen] == '_'))
                        vlen++;

                    char *varname = ft_substr(data->cmd, vstart, vlen);
                    char *value = get_env_var(varname);
                    free(varname);
                    token = str_append(token, value);

                    k = vstart + vlen;
                    start = k;
                }
                else
                    k++;
            }
            if (start < end)
                token = str_append(token, ft_substr(data->cmd, start, end - start));
            if (data->cmd[i] == '"') 
                i++;
        }
        else if (data->cmd[i] == '$')
        {
            start = i + 1;
            int vlen = 0;
            while (data->cmd[start + vlen] &&
                   (isalnum((unsigned char)data->cmd[start + vlen]) || data->cmd[start + vlen] == '_'))
                vlen++;

            char *varname = ft_substr(data->cmd, start, vlen);
            char *value = get_env_var(varname);
            free(varname);
            token = strdup(value);
            i = start + vlen;
        }
        else
        {
            start = i;
            while (data->cmd[i] && data->cmd[i] != '\'' && data->cmd[i] != '"' && data->cmd[i] != '$')
                i++;
            token = ft_substr(data->cmd, start, i - start);
        }
        if (token)
            temp[j++] = token;
    }
    temp[j] = NULL;
    return temp;
}

char *ft_strjoin_cmd(char **cmd)
{
    int len = 0;
    char *result;
    int i = 0;
    int k;

    if (!cmd || !cmd[0])
        return (NULL);
    while (cmd[i])
    {
        len += ft_strlen(cmd[i]);
        i++;
    }
    result = malloc(len + 1);
    if (!result)
        return(NULL);
    result[0] = '\0';
    i = 0;
    while (cmd[i])
    {
        ft_strlcat(result, cmd[i], ft_strlen(result) + ft_strlen(cmd[i]) + 1);
        i++;
    }
    printf("RESULT %s\n", result);
    return(result);
}

void expand_cmd(t_clean_cmd *data)
{
    char **token_cmd;

    token_cmd = aux_cmd(data);
    free(data->cmd);
    data->cmd= ft_strjoin_cmd(token_cmd);
}
