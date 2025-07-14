#include "../minishell.h"

void type_command(char *line, t_com *commands)
{
    int end;
    char *cmd = get_clean_command(line, &end);

    if (!cmd)
        return;
    init_struct(line, cmd, end, commands);
    free(cmd); 
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

    commands = create_struct(line, pipes);
    init_commands(line, commands);
    print_list(commands);
    return (commands);
}
