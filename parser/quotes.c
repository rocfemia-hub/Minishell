#include "../minishell.h"

int aux_quotes(char *line)
{
    int i = 0;
    char open_quote = 0; // 0 = ninguna, '\'' o '"'

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

int pipes_quotes(char *line)
{
    if (!quotes(line)) // hay comillas pero no estan cerradas, da error
        return (2);
    else // hay comillas y estan cerradas
        return (1);
}

int pipes_counter(char *line)
{
    int pipes;
    int i;
    int j;

    i = 0;
    j = 0;
    pipes = 0;
    while (line[i])
    {
        j = i;
        if (line[i] == '|')
        {
            while (j > 0 && line[j - 1] && line[j - 1] != 39 && line[j - 1] != 34)
                j--;
            if (j == 0) // no hay comillas porque no las encuentra en el bucle de arriba
                pipes++;
            else if (pipes_quotes(line + j -1) == 2) // comillas no cerradas
                pipes = -1;
            else if (pipes_quotes(line + j -1) == 1) // pipes como argumentos
                pipes = pipes;
        }
        i++;
    }
    return (pipes);
}