/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:30 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:37:32 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_cmd(char **cmd)
{
    int len;
    char *result;
    int i;
    int k;

    len = 0;
    i = -1;
    if (!cmd || !cmd[0])
        return (NULL);
    while (cmd[++i])
        len += ft_strlen(cmd[i]);
    result = malloc(len + 1);
    if (!result)
        return(NULL);
    result[0] = '\0';
    i = -1;
    while (cmd[++i])
        ft_strlcat(result, cmd[i], ft_strlen(result) + ft_strlen(cmd[i]) + 1);
    return(result);
}

char *handle_plain_text_args(char *line, int *i, t_vars *vars)
{
    int start;
    char *token;

    token = NULL;
    start = *i;
    while (line[*i] && line[*i] != '\'' && line[*i] != '"' && line[*i] != '$')
        (*i)++;
    token = ft_substr(line, start, *i - start);
    return(token);
}

char **process_aux_args(char *line, char **temp, t_vars *vars)
{
    int i;
    int j;
    char *token;

    i = 0;
    j = 0;
    while (line[i])
    {
        token = NULL;
        if (line[i] == '\'')
            token = handle_single_quotes(line, &i, vars);
        else if (line[i] == '"')
            token = handle_double_quotes(line, &i, vars);
        else if (line[i] == '$')
            token = handle_dollar(line, &i, vars);
        else
            token = handle_plain_text_args(line, &i, vars);
        if (token)
            temp[j++] = token;
    }
    temp[j] = NULL;
    return(temp);
}

char **aux_args(char *line, t_vars *vars)
{ 
    char **temp;

    temp = ft_calloc((256 + 1), sizeof(char *));
    if (!temp)
        return(NULL);
    return(process_aux_args(line, temp, vars));
}


char *expand_args(char *line, t_vars *vars)
{
    char **token_args;
    char *new_line;

    token_args = aux_args(line, vars);
    new_line = ft_strjoin_cmd(token_args);
    return(new_line);
}
