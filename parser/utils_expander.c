/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:56 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:36:58 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *handle_single_quotes(char *line, int *i, t_vars *vars)
{ 
    int start;
    char *token;
    int len;

    (*i)++; 
    start = *i; 
    while (line[*i] && line[*i] != '\'')
        (*i)++;
    len = *i - start;
    token = ft_substr(line, start, len);
    if (line[*i] == '\'')
        (*i)++; 
    return (token);
}

char *expand_var_in_quotes_args(char *line, int *k, int end, int *start, char *token, t_vars *vars)
{ // VARIABLES DENTRO DE COMILLAS DOBLES
    int vstart;
    int vlen;
    char *varname;
    char *value;

    vstart = *k + 1;
    vlen = 0;
    if (line[vstart] == '?')
    {
        value = ft_itoa(vars->exit_status);
        token = str_append(token, value);
        free(value);
        *k = vstart + 1;
        *start = *k;
        return (token);
    }
    if (!line[vstart] || !(ft_isalnum((unsigned char)line[vstart]) || line[vstart] == '_'))
    {
        token = str_append(token, "$");
        *k = vstart;
        *start = *k;
        return (token);
    }
    while (line[vstart + vlen] && (ft_isalnum((unsigned char)line[vstart + vlen]) || line[vstart + vlen] == '_'))
        vlen++;
    varname = ft_substr(line, vstart, vlen);
    value = get_env_var(varname);
    free(varname);
    token = str_append(token, value);
    *k = vstart + vlen;
    *start = *k;
    return(token);
}

char *process_inside_double_quotes(char *line, int start, int end, t_vars *vars)
{ //GESTION DE COMILLAS DOBLES FUNCION AUXILIAR
    int k;
    char *token;

    token = NULL;
    k = start;
    while (k < end)
    {
        if (line[k] == '$')
        {
            if (k > start)
                token = str_append(token, ft_substr(line, start, k - start));
            token = expand_var_in_quotes_args(line, &k, end, &start, token, vars);
        }
        else
            k++;
    }
    if (start < end)
        token = str_append(token, ft_substr(line, start, end - start));
    return(token);
}

char *handle_double_quotes(char *line, int *i, t_vars *vars)
{ //GESTION COMILLAS DOBLES
    int start;
    int end;
    char *token;
    char *inner;

    start = *i;
    (*i)++;
    end = *i;
    while (line[end] && line[end] != '"')
        end++;
    inner = process_inside_double_quotes(line, *i, end, vars);
    if (line[end] == '"')
        end++;
    *i = end;
    token = ft_strjoin("\"", inner);
    token = str_append(token, "\"");
    free(inner);
    return (token);
}

char *expand_var_in_quotes(char *cmd, int *k, int end, int *start, char *token, t_vars *vars)
{
    int vstart;
    int vlen;
    char *varname;
    char *value;

    vstart = *k + 1;
    vlen = 0;
    if (cmd[vstart] == '?')
    {
        value = ft_itoa(vars->exit_status);
        token = str_append(token, value);
        free(value);
        *k = vstart + 1;
        *start = *k;
        return(token);
    }
    if (!cmd[vstart] || !(ft_isalnum((unsigned char)cmd[vstart]) || cmd[vstart] == '_'))
    {
        token = str_append(token, "$");
        *k = vstart;
        *start = *k;
        return(token);
    }
    while (cmd[vstart + vlen] &&
           (ft_isalnum((unsigned char)cmd[vstart + vlen]) || cmd[vstart + vlen] == '_'))
        vlen++;
    varname = ft_substr(cmd, vstart, vlen);
    value = get_env_var(varname);
    free(varname);
    token = str_append(token, value);
    *k = vstart + vlen;
    *start = *k;
    return(token);
}
