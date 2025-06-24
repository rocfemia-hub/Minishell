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

void *how_is(char *line, t_com *temp) // me mira que es cada cosa para gestionarlas y meter cada cosa en la estructura
{
    int i = 0;
    char **split = ft_split_mini(line, ' '); //hago un split por espacios

    if (split[i] && ft_strlen(split[0]) > 0)
    {
        if (ft_strnstr(split[i], "echo", 4))
            echo_com(temp, line);
        if (ft_strnstr(split[i], "pwd", 3))
            pwd_com(temp, line);
        if (ft_strnstr(split[i], "cd", 2))
            cd_com(temp, line);
        if (ft_strnstr(split[i], "export", 6))
            export_com(temp, line);
        if (ft_strnstr(split[i], "unset", 5))
            unset_com(temp, line);
        if (ft_strnstr(split[i], "env", 3))
            env_com(temp, line);
        if (ft_strnstr(split[i], "exit", 4))
            exit_com(temp, line);
        else   
            not_built(temp, line);
    }
    // printf("Index: %d, command: %s, arg: %s, flag_built: %d, command_arg: %s\n", temp->index, temp->command, temp->arg,temp->flag_built, temp->command_arg);
}

void *init_commands(char **commands, t_com *temp) 
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
    char **split;
    t_com *temp;

    split = ft_split_mini(line, '|');
    if (!split)
        return (0);
    // printf_matrix(split); // debugueo contenido de la matriz, FALTA TODAVIA COSAS
    temp = init_struct(split); // inicializo la estructura con el indice
    init_commands(split, temp); // meto en la estructura que es cada cosa
    // printf("Index: %d, command: %s, arg: %s, flag_built: %d, command_arg: %s\n", commands->index, commands->command, commands->arg,commands->flag_built, commands->command_arg);
    return (temp);
}
