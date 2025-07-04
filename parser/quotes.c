#include "../minishell.h"

int aux_quotes(char *line)
{
    int i;
    char open_quote;

    i = 0;
    open_quote = 0; // 0 = ninguna, '\'' o '"'
    while (line[i])
    {
        if ((line[i] == '\'' || line[i] == '"'))
        {
            if (!open_quote)
                open_quote = line[i]; // abre comilla
            else if (line[i] == open_quote)
                open_quote = 0; // cierra comilla
            else
                ; // comilla dentro de otra → ignorar
        }
        i++;
    }
    return (open_quote == 0); // devuelve 1 si todo balanceado
}

int quotes(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 34 || line[i] == 39) // comillas dobles-34 y comillas simples-39
            if (aux_quotes(line) == 0)
                return (0);
        i++;
    }
    return (1);
}

int quotes_in_commands(char *line, t_com *temp)
{
    int i;
    char quotes;
    int counter;

    i = 0;
    quotes = 0;
    counter = 0;
    while (line[i])
    {
        if ((line[i] == '\'' || line[i] == '"'))
        {
            if (!quotes)
                quotes = line[i]; // abre comilla
            else if (line[i] == quotes)
                quotes = 0;
            if (counter > 2)
            {
                temp->command = ft_strdup("echo");
                return (0);
            }
        }
        i++;
    }
    return (quotes == 0);
}

int pipes_counter(char *line)
{
    int i = 0;
    int count = 0;
    char open_quote = 0;

    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!open_quote)
                open_quote = line[i]; // abre comilla
            else if (line[i] == open_quote)
                open_quote = 0;       // cierra comilla
        }
        else if (line[i] == '|' && !open_quote)
        {
            count++; // solo si NO estamos dentro de comillas
        }
        i++;
    }

    if (open_quote != 0)
        return -1; // comillas no cerradas

    return count;
}