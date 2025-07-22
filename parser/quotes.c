#include "../minishell.h"


void *clean_arg(t_com *commands)
{
    char *cleaned;
    int i = 0;
    int j = 0;
    char quote = 0;

    cleaned = malloc(ft_strlen(commands->args) + 1);
    if (!cleaned)
        return (NULL);
    while (commands->args[i])
    {
        if ((commands->args[i] == '\'' || commands->args[i] == '"'))
        {
            if (!quote) //open
                quote = commands->args[i];
            else if (quote == commands->args[i]) // close
                quote = 0;
            else
                cleaned[j++] = commands->args[i];
        }
        else
            cleaned[j++] = commands->args[i];
        i++;
    }
    cleaned[j] = '\0';
    free(commands->args);
    commands->args = cleaned;
    return (NULL);
}

char *clean_cmd(char *line, t_clean_cmd *data) 
{
    while (line[data->i] == ' ')
        data->i++;
    if (line[data->i] == '\'' || line[data->i] == '"')
    {
        data->quote = line[data->i]; 
        data->i++;
        data->start = data->i;
        while (line[data->i] && line[data->i] != data->quote)
        {
            if (line[data->i] == ' ') // spaces inside command - invalid
                return (ft_substr("error", 0, 5));
            data->i++;
        }
        if (!line[data->i]) // quotes not closed
            return (ft_substr("error", 0, 5));
        data->end = data->i;
        data->end_index = data->i + 1;
        return ft_substr(line, data->start, data->end - data->start);
    }
    data->start = data->i;
    while (line[data->i] && line[data->i] != ' ')
        data->i++;
    data->end = data->i;
    data->end_index = data->end;
    return (ft_substr(line, data->start, data->end - data->start));
}

// |, <, >, >>, <<
int pipes_counter(char *line)
{ // pipes
    int i;
    int count;
    char open_quote;

    i = 0;
    count = 0;
    open_quote = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!open_quote) //open
                open_quote = line[i]; 
            else if (line[i] == open_quote) //close
                open_quote = 0; 
        }
        else if (line[i] == '|' && !open_quote)
            count++; 
        i++;
    }
    if (open_quote != 0)
        return (-1); 
    return (count);
}
