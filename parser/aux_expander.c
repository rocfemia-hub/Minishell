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

    nbr = ft_itoa(vars->exit_error);
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

char *str_append(char *dest, const char *src)
{
    char *tmp;

    if (!dest)
        dest = ft_strdup(src);
    else
    {
        tmp = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
        ft_strlcpy(tmp, dest, ft_strlen(tmp) + ft_strlen(dest) + 1);
        ft_strlcat(tmp, src, ft_strlen(tmp) + ft_strlen(src) + 1);
        free(dest);
        dest = tmp;
    }
    return(dest);
}

char *ft_strjoin_cmd(char **cmd)
{ // ME CONVIERTE DE CHAR ** A CHAR *
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

char *extract_varname(char *line, int start, int *vlen)
{ //GESTION DE VARIABLES FUERA DE COMILLAS FUNCION AUXILIAR
    char *varname;
    
    *vlen = 0;
    while (line[start + *vlen] &&
           (ft_isalnum((unsigned char)line[start + *vlen]) || line[start + *vlen] == '_'))
        (*vlen)++;
    varname = ft_substr(line, start, *vlen);
    return (varname);
}

char *handle_dollar(char *line, int *i, t_vars *vars)
{ //GESTION DE VARIABLES FUERA DE COMILLAS
    int start;
    int vlen;
    char *token;
    char *varname;
    char *value;

    token = NULL;
    start = *i + 1; // posición después del $
    if (line[start] == '?')
    {
        token = handle_inter(vars);  // convierte exit_error a string
        *i = start + 1;
    }
    else if (ft_isalnum((unsigned char)line[start]) || line[start] == '_')
    {
        varname = extract_varname(line, start, &vlen);
        value = get_env_var(varname);
        free(varname);
        token = ft_strdup(value);
        *i = start + vlen;
    }
    else
    {
        token = ft_strdup("$");
        *i = start;
    }
    return (token);
}

