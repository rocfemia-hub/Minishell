#include "../minishell.h"

void echo_com(t_com *temp, char *line)
{

}

void pwd_com(t_com *temp, char *line) // gestiona el pwd para meter cada cosa en la estructura
{
    // printf("ha entrado a pwd\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'p' && line[i + 1] == 'w' && line[i + 2] == 'd' && line[i + 3] == ' ')
    {
        temp->command = ft_strdup("pwd");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(line + i + 4);
    }
}

void cd_com(t_com *temp, char *line) // gestiona el cd para meter cada cosa en la estructura
{
    // printf("ha entrado a cd\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'c' && line[i + 1] == 'd' && line[i + 4] == ' ')
    {
        temp->command = ft_strdup("cd");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(line + i + 3);
    }
}

void export_com(t_com *temp, char *line) // gestiona el export para meter cada cosa en la estructura
{
    // printf("ha entrado a export\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'p' && line[i + 3] == 'o' && line[i + 4] == 'r' && line[i + 5] == 't' && line[i + 6] == ' ')
    {
        temp->command = ft_strdup("export");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(line + i + 7);
    }
}

void unset_com(t_com *temp, char *line) // gestiona el unset para meter cada cosa en la estructura
{
    // printf("ha entrado a unset\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'u' && line[i + 1] == 'n' && line[i + 2] == 's' && line[i + 3] == 'e' && line[i + 4] == 't' && line[i + 5] == ' ')
    {
        temp->command = ft_strdup("unset");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(line + i + 6);
    }
}
