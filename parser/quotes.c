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

int words_in_quotes(char *line, int start, int end)
{
    int i;
    int in_word;
    int word_count;

    i = start;
    in_word = 0;
    word_count = 0;
    while (i < end)
    {
        if (line[i] != ' ' && !in_word)
        {
            in_word = 1;
            word_count++;
        }
        else if (line[i] == ' ')
            in_word = 0;
        i++;
    }
    return (word_count > 1);
}
char *get_clean_command(char *line, int *end_index)
{
    int i = 0;
    int j;
    char quote;

    while (line[i] == ' ')
        i++;
    j = i;
    if (line[i] == '\'' || line[i] == '"')
    {
        quote = line[i];
        j += 1;
        int start = j;
        while (line[j] && line[j] != quote)
            j++;
        if (line[j] == quote)
        {
            if (words_in_quotes(line, start, j))
                return NULL;
            if (end_index)
                *end_index = j + 1;
            return (ft_substr(line, start, j - start));
        }
        return NULL; // comillas no cerradas
    }
    while (line[j] && line[j] != ' ')
        j++;
    if (end_index)
        *end_index = j;
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

