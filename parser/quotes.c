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

char *get_clean_command(char *line, int *end_index)
{
    int i = 0;
    int start = 0;
    int end = 0;
    char quote;
    char *cmd;

    while (line[i] == ' ') // Saltar espacios al inicio
        i++;
    if (line[i] == '\'' || line[i] == '"')
    {
        quote = line[i];
        i++;
        start = i;
        while (line[i] && line[i] != quote) // Buscar comilla de cierre
        {
            if (line[i] == ' ') // espacio dentro de comillas: inválido
                return NULL;
            i++;
        }
        if (!line[i]) // no encontró cierre
            return (NULL);
        end = i;
        if (end_index)
            *end_index = i + 1;
        return (ft_substr(line, start, end - start)); // sin comillas
    }
    start = i;
    while (line[i] && line[i] != ' ')   // Sin comillas: comando termina en espacio o final
        i++;
    end = i;
    if (end_index)
        *end_index = end;
    return ft_substr(line, start, end - start);
}


int pipes_counter(char *line)
{ //cuenta las pipes que no son argumentos
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

char *strip_outer_quotes(char *arg)
{
    int len;

    if (!arg)
        return NULL;
    len = ft_strlen(arg);
    if (len > 1 && ((arg[0] == '\'' || arg[0] == '"') && arg[len - 1] == arg[0]))
    {
        char *new_arg = ft_substr(arg, 1, len - 2);
        free(arg);
        return new_arg;
    }
    return(arg);
}

