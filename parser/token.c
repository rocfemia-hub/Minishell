#include "../minishell.h"

t_com *init_struct(char *line, t_pipes pipes)
{
    int i ;
    t_com *new;
    t_com *head;

    i = 0;
    pipes.pipes = pipes_counter(line); // me cuenta los pipes que hay, sin qeu sean argumentos
    head = lstnew(i);
    if (!head)
        return (NULL);
    pipes.pipes--;
    while (pipes.pipes > 0)
    {
        new = lstnew(i);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
        pipes.pipes--;
    }
    return (head);
}

void init_commmands(char **split, t_com commands)
{

}


t_com *token(char *line) // me separa la array de comandos, arg y flags en una estructura
{
    t_com *commands;
    t_pipes pipes;
    char **split;

    split = ft_split_mini(line, ' ');
    commands = init_struct(line, pipes);
    init_commands(split, commands);
    // ft_free_free(split);
    return (commands);
}
