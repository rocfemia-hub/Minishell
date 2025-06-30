#include "../minishell.h"

int pipes_counter(char *line)
{
    int pipes;
    int i;

    i = 0;
    pipes = 0;
    while (line[i])
    {
        if (line[i] == '|')
        {
            if (pipes_quotes(line + i - 1) == 2)
            {
                printf("devuelve 2\n");
                pipes = -1;
            }
            if (pipes_quotes(line + i - 1) == 1)
            {
                printf("devuelve 1\n");
                pipes++;
            }
            if (pipes_quotes(line + i - 1) == 0)
            {
                printf("devuelve 0\n");
                pipes = pipes;
            }
        }
        i++;
    }
    return (pipes);
}
t_com *init_struct(char *line) // me crea la lista donde voy a meter los index y los fd_out
{
    int i;
    int pipes;
    t_com *new;
    t_com *head;

    pipes = pipes_counter(line); // me cuenta los pipes que hay, sin qeu sean argumentos
    printf("%d\n", pipes);
    head = lstnew(i);
    if (!head)
        return (NULL);
    while (line[++i] && i < pipes + 1)
    {
        new = lstnew(i);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
    }
    return (head);
}

void *how_is(char *line, t_com *temp) // me mira que es cada cosa y llama a las funciones que lo va a meter en la estructura
{
}

void *init_commands(char **commands /*split por pipes*/, t_com *temp) // me va llamando a la funcion que mira lo que es cada comando, pasando cada array de la matriz que hemos separado en pipes
{
    int i = 0;

    while (temp && commands[i])
    {
        how_is(commands[i], temp);
        i++;
        temp = temp->next;
    }
}

t_com *token(char *line) // me separa la array de comandos, arg y flags en una estructura
{
    t_com *temp;
    temp = init_struct(line);
    // init_commands(split, temp);
    // ft_free_free(split);
    return (temp);
}
