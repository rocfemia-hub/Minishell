#include "../minishell.h"

void type_command(char *line, t_com *commands)
{
    t_clean_cmd data;

    ft_bzero(&data, sizeof(t_clean_cmd));
    data.cmd = clean_cmd(line, &data);
    if (!data.cmd || !ft_strncmp(data.cmd, "error", 5))
    {
        commands->command = ft_strdup("error");
        commands->args = NULL;
        return;
    }
    init_struct(line, data.cmd, data.end_index, commands);
    free(data.cmd);
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
            if (!quote) // quotes open or closed
                quote = line[i];
            else if (quote == line[i])
                quote = 0;
        }
        if (line[i] == '|' && !quote) // < << >> <
        {
            line[i] = '\0';
            type_command(line + start, current);
            start = i + 1;
            current = current->next;
        }
        i++;
    }
    if (current) // last command and arg
        type_command(line + start, current);
}

t_com *token(char *line) 
{
    t_com *commands;
    t_pipes pipes;

    commands = create_struct(line, pipes);
    if (!commands)
        return(NULL);
    init_commands(line, commands);
    check_arg(commands);
    print_list(commands);
    return (commands);
}
