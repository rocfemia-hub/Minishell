/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:34 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 01:06:03 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *str_append(char *dest, const char *src)
{
    char *tmp;

    if (!dest)
		dest = ft_strdup(src);
    else
    {
        tmp = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
		if (!tmp)
			return (NULL);
        ft_strlcpy(tmp, dest, ft_strlen(tmp) + ft_strlen(dest) + 1);
        ft_strlcat(tmp, src, ft_strlen(tmp) + ft_strlen(src) + 1);
        free(dest);
        dest = tmp;
    }
    return(dest);
}

char *handle_plain_text(char *cmd, int *i, t_vars *vars)
{
    int start;
    
	if (!vars)
		return (NULL);
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

