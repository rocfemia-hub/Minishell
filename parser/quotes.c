#include "../minishell.h"

int aux_quotes(char *line, t_temp *temp)
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
    temp->i = i;
    return (open_quote == 0); // devuelve 1 si todo balanceado
}

int quotes(char *line, t_temp *temp)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 34 || line[i] == 39) // comillas dobles-34 y comillas simples-39
            if (aux_quotes(line, temp) == 0)
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

int pipes_quotes(char *line, t_temp *temp)
{
    if (!quotes(line, temp)) // hay comillas pero no estan cerradas, da error
        return (2);
    else // hay comillas y estan cerradas
        return (1);
}

int pipes_counter(char *line)
{
    t_temp *temp = calloc(1, sizeof(t_temp));
    if (!temp)
        return (-1); // o manejar error
    while (line[temp->i])
    {
        if (line[temp->i] == '|')
        {
            while (temp->j > 0 && line[temp->j - 1] && line[temp->j - 1] != 39 && line[temp->j - 1] != 34) // va hacia atras hasta que se encuentra comillas
                temp->j--;
            if (temp->j == 0) // no hay comillas porque no las encuentra en el bucle de arriba
                temp->pipes++;
            else if (pipes_quotes(line + temp->j - 1, temp) == 2) // comillas no cerradas
                temp->flag = 1;
            else if (pipes_quotes(line + temp->j - 1, temp) == 1) // pipes como argumentos
                temp->pipes = temp->pipes;
            temp->j = temp->i;
            printf("i despues de ver si estan cerradas o abiertas: %d\n", temp->i);
            printf("--> j despues de ver si estan cerradas o abiertas: %d\n", temp->j);
        }
        if (temp->flag == 1)
            return (-1);
        temp->i++;;
    }
    return (temp->pipes);
}
