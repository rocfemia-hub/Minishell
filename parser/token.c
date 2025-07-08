#include "../minishell.h"

t_com *init_struct(char *line, t_pipes pipes)
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


void type_command(char *line, t_com *commands)
{
    // printf("line: %s\n", line);
    if (!ft_strncmp(line, "echo", 4))
        echo_com(commands, line);
    else if (!ft_strncmp(line, "pwd", 3))
        pwd_com(commands, line);
    else if (!ft_strncmp(line, "cd", 2))
        cd_com(commands, line);
    else if (!ft_strncmp(line, "export", 6))
        export_com(commands, line);
    else if (!ft_strncmp(line, "unset", 5))
        unset_com(commands, line);
    else if (!ft_strncmp(line, "env", 3))
        env_com(commands, line);
    else if (!ft_strncmp(line, "exit", 4))
        exit_com(commands, line);
    else
        not_built(commands, line);
}

void init_commands(char *line, t_com *commands)
{
    int i = 0; 
    int start = 0;
    char quote = 0;
    t_com *current = commands;

    while (line[i])
    {
        if ((line[i] == '"' || line[i] == '\''))
        {
            if (!quote)
                quote = line[i];
            else if (quote == line[i])
                quote = 0;
        }
        if (line[i] == '|' && !quote) 
        {
            line[i] = '\0'; 
            type_command(line + start, current);
            start = i + 1;
            current = current->next;
        }
        i++;
    }
    if (current)  // Último comando después del último pipe (o único comando)
        type_command(line + start, current);
}


t_com *token(char *line) // me separa la array de comandos, arg y flags en una estructura
{
    t_com *commands;
    t_pipes pipes;

    commands = init_struct(line, pipes);
    init_commands(line, commands);
    // print_list(commands);
    return (commands);
}
