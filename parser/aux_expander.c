/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:37:54 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *handle_inter(t_vars *vars)
{
    char *nbr;

    nbr = ft_itoa(vars->exit_status);
    return (nbr);
}

char *get_env_var(const char *var)
{
    char *value;
    
    value = getenv(var);
    if (value != NULL)
        return(value);
    else
        return("");
}

char *extract_varname(char *line, int start, int *vlen)
{
    char *varname;
    
    *vlen = 0;
    while (line[start + *vlen] &&
           (ft_isalnum((unsigned char)line[start + *vlen]) || line[start + *vlen] == '_'))
        (*vlen)++;
    varname = ft_substr(line, start, *vlen);
    return (varname);
}

static char *handle_var_expansion(char *line, int start, int *vlen)
{
    char *varname;
    char *value;
    char *token;

    varname = extract_varname(line, start, vlen);
    value = get_env_var(varname);
    free(varname);
    token = ft_strdup(value);
    return (token);
}

char *handle_dollar(char *line, int *i, t_vars *vars)
{
    int start;
    int vlen;
    char *token;

    token = NULL;
    start = *i + 1;
    if (line[start] == '?')
    {
        token = handle_inter(vars);
        *i = start + 1;
    }
    else if (ft_isalnum((unsigned char)line[start]) || line[start] == '_')
    {
        token = handle_var_expansion(line, start, &vlen);
        *i = start + vlen;
    }
    else
    {
        token = ft_strdup("$");
        *i = start;
    }
    return (token);
}

