#include "../minishell.h"

char *handle_plain_text_args(char *line, int *i)
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

char **process_aux_args(char *line, char **temp)
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
            token = handle_single_quotes(line, &i);
        else if (line[i] == '"')
            token = handle_double_quotes(line, &i);
        else if (line[i] == '$')
            token = handle_dollar(line, &i);
        else
            token = handle_plain_text_args(line, &i);
        if (token)
            temp[j++] = token;
    }
    temp[j] = NULL;
    return(temp);
}

char **aux_args(char *line)
{ 
    char **temp;

    temp = ft_calloc((256 + 1), sizeof(char *));
    if (!temp)
        return(NULL);
    return(process_aux_args(line, temp));
}


char *expand_args(char *line)
{
    char **token_args;
    char *new_line;

    token_args = aux_args(line);
    new_line = ft_strjoin_cmd(token_args);
    return(new_line);
}
