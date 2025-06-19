#include "../minishell.h"

int lengh_matrix (char **matrix) // me dice la longitud de la matriz donde estoy guardando todos los comandos
{
    int len;

    len = 0;
    while (matrix[len])
        len++;
    return(len);
}

t_com *init_command(char **commands) // para el final, me crea la lista donde voy a meter los comandos y argumentos
{
    int i;
    t_com *new;
    t_com *head;

    i = 0;
    head = lstnew(commands[i]);
    if (!head)
        return (NULL);
    while (commands[++i])
    {
        new = lstnew(commands[i]);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
    }
    return (head);
}

int parser(char *line)
{
    char **split;
    t_com *commands;
    int len_matrix;

    split = ft_split_new(line);
    if (!split)
        return (0);
    // printf_matrix(split); //debugueo contenido de la matriz, FALTA TODAVIA COSAS
    len_matrix = lengh_matrix(split);
    // printf("%d\n", len_matrix); // debugueo longitud de la matriz, FALTA TODAVIA COSAS
    commands = ft_calloc(1, sizeof(t_com));
    commands = init_command(split);
    return (1);
}
