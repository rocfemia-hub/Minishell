#include "../minishell.h"

t_com *init_struct(char *line) // me crea la lista donde voy a meter los index y los fd_out
{
    int i;
    int pipes;
    t_com *new;
    t_com *head;

    pipes = pipes_counter(line); // me cuenta los pipes que hay, sin qeu sean argumentos
    printf("pipes: %d\n", pipes);
    head = lstnew(i);
    if (!head)
        return (NULL);
    pipes--;
    while (pipes > 0)
    {
        new = lstnew(i);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
        pipes--;
    }
    return (head);
}


t_com *token(char *line) // me separa la array de comandos, arg y flags en una estructura
{
    t_com *temp;
    char **split;

    split = ft_split_mini(line, ' ');
    temp = init_struct(line);
    // ft_free_free(split);
    return (temp);
}
