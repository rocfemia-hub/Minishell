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

char *handle_plain_text(char *cmd, int *i, t_vars *vars)
{
    int start;
    
    start = *i;
    while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '"' && cmd[*i] != '$')
        (*i)++;
    return(ft_substr(cmd, start, *i - start));
}

char *aux_cmd(t_clean_cmd *data, t_vars *vars)
{
    int i;
    char *token;
    char *result;
    char *temp;

    i = 0;
    result = ft_calloc(1, 1); 
    while (data->cmd[i])
    {
        if (data->cmd[i] == '\'')
            token = handle_single_quotes(data->cmd, &i, vars);
        else if (data->cmd[i] == '"')
            token = handle_double_quotes(data->cmd, &i, vars); 
        else if (data->cmd[i] == '$')
            token = handle_dollar(data->cmd, &i, vars); 
        else
            token = handle_plain_text(data->cmd, &i, vars);
        if (token)
        {
            temp = ft_strjoin(result, token);
            free(result);
            free(token);
            result = temp;
        }
    }
    data->end_index = i;
    return (result);
}

int expand_cmd(t_clean_cmd *data, t_vars *vars)
{
    char *expanded;

    expanded = aux_cmd(data, vars);
    if (ft_strlen(expanded) < 1) //SI LA EXPANSION NO EXISTE DEVUELVE 0 PARA QUE FUERA COJA EL SIGUIENTE COMANDO
        return (0);
    free(data->cmd);
    data->cmd = expanded;
    return (1);
}

