#include "../minishell.h"

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
    size_t ldest;
    size_t lsrc;
    char *tmp;

    if (!src)
        return(dest);
    if (!dest)
        return strdup(src); /* strdup devuelve NULL si falla */
    ldest = ft_strlen(dest);
    lsrc  = ft_strlen(src);
    tmp = malloc(ldest + lsrc + 1);
    if (!tmp)
    {
        free(dest);
        return NULL;
    }
    ft_memcpy(tmp, dest, ldest);
    ft_memcpy(tmp + ldest, src, lsrc);
    tmp[ldest + lsrc] = '\0';
    free(dest);
    return tmp;
}

char *ft_strjoin_cmd(char **cmd)
{
    int len;
    char *result;
    int i;

    len = 0;
    i = 0;
    if (!cmd || !cmd[0])
        return (NULL);
    while (cmd[i])
    {
        len += ft_strlen(cmd[i]);
        i++;
    }
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    result[0] = '\0';
    i = 0;
    while (cmd[i])
    {
        ft_strlcat(result, cmd[i], len + 1);
        i++;
    }
    return (result);
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

char *handle_dollar(char *line, int *i)
{  //GESTION DE VARIABLES FUERA DE COMILLAS
    int start;
    int vlen;
    char *token;
    char *varname;
    char *value;

    token = NULL;
    start = *i + 1;
    if (ft_isalnum((unsigned char)line[start]) || line[start] == '_')
    {
        varname = extract_varname(line, start, &vlen);
        value = get_env_var(varname);
        free(varname);
        token = strdup(value);
        *i = start + vlen;
    }
    else
    {
        token = strdup("");
        *i = start;
    }
    return (token);
}
