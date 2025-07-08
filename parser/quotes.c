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
                ; // comilla dentro de otra se ignorar
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

char *get_clean_command(char *line)
{
    int i = 0;
    char quote;

    while (line[i] == ' ')
        i++;
    if (line[i] == '\'' || line[i] == '"')
    {
        quote = line[i];
        int j = i + 1;
        while (line[j] && line[j] != quote)
            j++;
        if (line[j] == quote)
            return (ft_substr(line, i + 1, j - i - 1));  // devuelve solo la palabra sin comillas
    }
    int j = i; // Si no hay comillas, va hasta primer espacio
    while (line[j] && line[j] != ' ')
        j++;
    return (ft_substr(line, i, j - i));
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
                open_quote = 0; // cierra comilla
        }
        else if (line[i] == '|' && !open_quote)
            count++; // solo si NO estamos dentro de comillas
        i++;
    }
    if (open_quote != 0)
        return (-1); // comillas no cerradas
    return count;
}

