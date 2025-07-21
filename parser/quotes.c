#include "../minishell.h"

int aux_quotes(char *line)
{
    int i;
    char open_quote;

    i = 0;
    open_quote = 0; 
    while (line[i])
    {
        if ((line[i] == '\'' || line[i] == '"'))
        {
            if (!open_quote)
                open_quote = line[i]; 
            else if (line[i] == open_quote)
                open_quote = 0;
            else
                ;
        }
        i++;
    }
    return (open_quote == 0);
}

int quotes(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"') 
            if (aux_quotes(line) == 0)
                return (0);
        i++;
    }
    return (1); // return 1 if is okay 
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


int pipes_counter(char *line)
{ // pipes
    int i = 0;
    int count = 0;
    char open_quote = 0;

    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!open_quote)
                open_quote = line[i]; 
            else if (line[i] == open_quote)
                open_quote = 0; 
        }
        else if (line[i] == '|' && !open_quote)
            count++; 
        i++;
    }
    if (open_quote != 0)
        return (-1); 
    return count;
}
