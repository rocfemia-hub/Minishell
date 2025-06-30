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

int quotes(char *line, t_com *temp)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 34 || line[i] == 39) // comillas dobles-34 y comillas simples-39
            if (aux_quotes(line) == 0)
            {
                temp->command = ft_strdup("error");
                return (0);
            }
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
    int i = 0;
    int counter_simple = 0;
    int counter_doble = 0;

    if (!ft_strchr(line, '\'') || !ft_strchr(line, '"'))
    {
        printf("entra a que no hay comillas\n");
        return (0); //no hay comillas
    }
    while (line[i])
    {
        if (line[i] == 39) // simple
        {
            printf("simple_counter: %d\n", counter_simple);
            counter_simple++;
            while (line[i])
            {
                if (line[i] == 39)
                    counter_simple++;
                if (counter_simple > 2)
                    return (1); //comillas cerradas
                i++;
            }
            if (counter_simple == 1)
                return(2); //comillas sin cerrar
        }
        if (line[i] == 34) // doble
        {
            printf("double_counter: %d\n", counter_doble);
            counter_doble++;
            while (line[i])
            {
                if (line[i] == 34)
                    counter_doble++;
                if (counter_doble > 2)
                    return (1); //comillas cerradas
                i++;
            }
            if (counter_doble == 1)
                return(2); //comillas sin cerrar
        }
        i++;
    }
}
