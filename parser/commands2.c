#include "../minishell.h"

void env_com(t_com *temp, char *line) // gestiona el env para meter cada cosa en la estructura
{
    // printf("ha entrado a env\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'e' && line[i + 1] == 'n' && line[i + 2] == 'v' && line[i + 3] == ' ')
    {
        temp->command = ft_strdup("env");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(line + i + 4);
    }
}

void exit_com(t_com *temp, char *line) // gestiona el exit para meter cada cosa en la estructura
{
    // printf("ha entrado a exit\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    if (line[i] && line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'i' && line[i + 3] == 't' && line[i + 4] == ' ')
    {
        temp->command = ft_strdup("exit");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(line + i + 5);
    }
}

void *not_built(t_com *temp, char *line)
{
    // printf("ha entrado a not_built\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    char **split = ft_split_mini(line + i, ' '); //hago un split por espacios
    temp->command = split[0];
    temp->command_arg = ft_strdup(line + i);
    temp->arg = ft_strdup(line + i);
    temp->flag_built = 0;
}