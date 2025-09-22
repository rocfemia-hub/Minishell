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

char *handle_plain_text(char *cmd, int *i)
{
    int start;
    
    start = *i;
    while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '"' && cmd[*i] != '$')
        (*i)++;
    return(ft_substr(cmd, start, *i - start));
}

char **aux_cmd(t_clean_cmd *data)
{
    char **temp;
    int i;
    int j;
    char *token;

    i = 0;
    j = 0;
    temp = malloc(sizeof(char *) * 256);
    while (data->cmd[i])
    {
        if (data->cmd[i] == '\'')
            token = handle_single_quotes(data->cmd, &i);
        else if (data->cmd[i] == '"')
            token = handle_double_quotes(data->cmd, &i);
        else if (data->cmd[i] == '$')
            token = handle_dollar(data->cmd, &i);
        else
            token = handle_plain_text(data->cmd, &i);
        if (token)
            temp[j++] = token;
    }
    temp[j] = NULL;
    data->end_index = i;
    return(temp);
}


void expand_cmd(t_clean_cmd *data)
{
    char **token_cmd;

    token_cmd = aux_cmd(data);
    free(data->cmd);
    data->cmd= ft_strjoin_cmd(token_cmd);
}