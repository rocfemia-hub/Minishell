#include "../minishell.h"

void echo_com(t_com *temp, char *line) // echo_com implementada
{
	int i;

	i = 0;
    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "echo", 4) == 0 && (line[i + 4] == ' ' || line[i + 4] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("echo");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        if (line[i + 4] == ' ') // Si hay espacio después de "echo" significa que hay argumentos
            temp->arg = ft_strdup(line + i + 5);
        else
            temp->arg = ft_strdup(""); // Solo "echo" sin argumentos
    }
}

void pwd_com(t_com *temp, char *line) // pwd_com modificada
{
    // printf("ha entrado a pwd\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "pwd", 3) == 0 && (line[i + 3] == ' ' || line[i + 3] == '\0')) // debe haber espacio o ser el final de la string
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
