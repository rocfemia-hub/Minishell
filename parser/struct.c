#include "../minishell.h"

char *ft_strjoin_mini(int len, t_com *commands)
{
    int i;
    char *cmd_arg;
    int j;

    i = 0;
    j = 0;
    cmd_arg = calloc(len, sizeof(char));
    while (commands->command[i])
    {
        cmd_arg[j] = commands->command[i];
        i++;
        j++;
    }
    cmd_arg[j] = ' ';
    j++;
    i = 0;
    while (commands->arg[i])
    {
        cmd_arg[j] = commands->arg[i];
        i++;
        j++;
    }
    cmd_arg[j] = '\0';
}

t_com *create_struct(char *line, t_pipes pipes)
{
    int i = 0;
    t_com *new;
    t_com *head;

    pipes.pipes = pipes_counter(line); // me cuenta las pipes que no estan como argumento
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
    int len;

    if (!cmd || !line)
        return;
    commands->command = ft_substr(cmd, 0, ft_strlen(cmd) + 1);
    while (line[end] == ' ') // Saltar espacios después del comando
        end++;
    commands->arg = ft_substr(line, end, ft_strlen(line) - end);
    len = ft_strlen(commands->command) + ft_strlen(commands->arg) + 2; // lomgitud que va a tener cmd_arg;
    commands->command_arg = ft_strjoin_mini(len, commands);
    commands->flag_built = 1; // falta un if para saber si es built o no 
}
