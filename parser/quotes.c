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

#include <stdlib.h>
#include <string.h>

// Verifica si la comilla inicial está escapada
int is_escaped(const char *str, int pos)
{
    int count = 0;
    pos--;
    while (pos >= 0 && str[pos] == '\\')
    {
        count++;
        pos--;
    }
    return (count % 2 == 1); // impar → está escapada
}

char *parse_line_bash_flat(const char *line)
{
    int i = 0; 
    int j = 0;
    int len = strlen(line);
    char quote = 0;
    char *result = malloc(len * 2 + 1); // espacio suficiente por si se expande
    int need_space = 0;

    if (!result)
        return NULL;
    while (i < len)
    {
        while (line[i] == ' ') // Saltar espacios iniciales
            i++;
        if (i >= len)
            break;
        if (need_space)
            result[j++] = ' ';
        need_space = 1;
        quote = 0;
        while (i < len && (quote || line[i] != ' '))
        {
            if (!quote && (line[i] == '\'' || line[i] == '"'))
                quote = line[i++];
            else if (quote && line[i] == quote)
            {
                quote = 0;
                i++;
            }
            else if ((quote == '"' && line[i] == '\\' && (line[i + 1] == '"' || line[i + 1] == '\\' ||
                line[i + 1] == '$' || line[i + 1] == '`')) || (!quote && line[i] == '\\' && line[i + 1]))
            {
                result[j++] = line[i + 1];
                i += 2;
            }
            else
                result[j++] = line[i++];
        }
    }
    result[j] = '\0';
    return result;
}
