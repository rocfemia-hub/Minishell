#include "../minishell.h"

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

char **aux_args(char *line)
{
    char **temp = malloc(sizeof(char *) * 256);
    int i = 0, j = 0, start;

    while (line[i])
    {
        char *token = NULL;
        if (line[i] == '\'')
        {
            i++;
            start = i;
            while (line[i] && line[i] != '\'')
                i++;
            if (i > start)
                token = ft_substr(line, start, i - start);
            if (line[i] == '\'')
                i++;
        }
        else if (line[i] == '"')
        {
            i++;
            start = i;
            while (line[i] && line[i] != '"')
                i++;
            int end = i;
            int k = start;
            while (k < end)
            {
                if (line[k] == '$')
                {
                    if (k > start)
                        token = str_append(token, ft_substr(line, start, k - start));
                    int vstart = k + 1;
                    int vlen = 0;
                    if (!line[vstart] ||
                        !(isalnum((unsigned char)line[vstart]) || line[vstart] == '_'))
                    {
                        token = str_append(token, "$");
                        k = vstart;
                        start = k;
                        continue;
                    }
                    while (line[vstart + vlen] &&
                           (isalnum((unsigned char)line[vstart + vlen]) || line[vstart + vlen] == '_'))
                        vlen++;

                    char *varname = ft_substr(line, vstart, vlen);
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
                token = str_append(token, ft_substr(line, start, end - start));
            if (line[i] == '"')
                i++;
        }
        else if (line[i] == '$')
        {
            start = i + 1;
            int vlen = 0;
            if (!line[start] || !(isalnum((unsigned char)line[start]) || line[start] == '_'))
            {
                token = strdup("$");
                i = start;
            }
            else
            {
                while (line[start + vlen] &&
                       (isalnum((unsigned char)line[start + vlen]) || line[start + vlen] == '_'))
                    vlen++;
                char *varname = ft_substr(line, start, vlen);
                char *value = get_env_var(varname);
                free(varname);
                token = strdup(value);
                i = start + vlen;
            }
        }
        else
        {
            start = i;
            while (line[i] && line[i] != '\'' && line[i] != '"' && line[i] != '$')
                i++;
            token = ft_substr(line, start, i - start);
        }
        if (token)
            temp[j++] = token;
    }
    temp[j] = NULL;
    return (temp);
}


char *expand_args(char *line)
{
    char **token_args;
    char *new_line;

    token_args = aux_args(line);
    new_line = ft_strjoin_cmd(token_args);
    return(new_line);
}