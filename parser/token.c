#include "../minishell.h"

t_com *init_struct(char **commands) // me crea la lista donde voy a meter los index
{
    int i;
    t_com *new;
    t_com *head;

    i = 0;
    head = lstnew(i);
    if (!head)
        return (NULL);
    while (commands[++i])
    {
        new = lstnew(i);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
    }
    return (head);
}

void *not_command(t_com *temp)
{

}

void *how_is(char *line, t_com *temp) // me mira que es cada cosa para gestionarlas y meter cada cosa en la estructura
{
    int i = 0;
    char **split = ft_split_normal(line, ' ');

    while (split[i])
    {
        if (ft_strncmp(split[i], "echo", 4))
            echo_com(&temp, line);
        if (ft_strncmp(split[i], "pwd", 3))
            pwd_com(&temp, line);
        if (ft_strncmp(split[i], "cd", 2))
            cd_com(&temp, line);
        if (ft_strncmp(split[i], "export", 6))
            export_com(&temp, line);
        if (ft_strncmp(split[i], "unset", 5))
            unset_com(&temp, line);
        if (ft_strncmp(split[i], "env", 3))
            env_com(&temp, line);
        if (ft_strncmp(split[i], "exit", 4))
            exit_com(&temp, line);
        else   
            not_command(&temp);
        i++;
    }
}

t_com *init_commands(char **commands, t_com *temp) 
{
    int i = 0;
    char *line;

    while (i < temp->index)
    {
        how_is(commands[i], &temp);
    }
}

int token(char *line) // me separa la array de comandos, arg y flags en una estructura
{
    char **split;
    t_com *temp;
    t_com *commands;
    int len_matrix;

    split = ft_split_normal(line, '|');
    if (!split)
        return (0);
    // printf_matrix(split); // debugueo contenido de la matriz, FALTA TODAVIA COSAS
    commands = init_struct(split);             // inicializo la estructura con el indice
    init_commands(split, &commands); // meto en la estructura que es cada cosa
    return (1);
}
