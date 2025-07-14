#include "../minishell.h"

t_com *create_struct(char *line, t_pipes pipes)
{
    int i = 0;
    t_com *new;
    t_com *head;

    pipes.pipes = pipes_counter(line); //me cuenta las pipes que no estan como argumento
    if (pipes.pipes < 0)
        return (NULL); 
    head = lstnew(i);
    if (!head)
        return (NULL);
    while (++i <= pipes.pipes) // crea nodos necesarios
    {
        new = lstnew(i);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
    }
    return (head);
}

void init_struct(char *line, char *cmd, int end, t_com *commands)
{
    if (!cmd || !line)
        return ;
    commands->cmd_arg = ft_calloc(3, sizeof(char *));
    commands->cmd_arg[0] = ft_substr(cmd, 0, ft_strlen(cmd));
    while (line[end] == ' ') // Saltar espacios después del comando
        end++;
    commands->cmd_arg[1] = ft_substr(line, end, ft_strlen(line) - end);
}
