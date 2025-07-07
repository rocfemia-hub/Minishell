#include "../minishell.h"

void echo_com(t_com *temp, char *line)
{ // echo_com implementada (ro)
	// printf("ha entrado a echo\n");
	int i;
	int j;

	i = 0;
	j = 0;
    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "echo", 4) == 0 && (line[i + 4] == ' ' || line[i + 4] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("echo");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        if (line[i + 4] == ' ') // Si hay espacio después de "echo" significa que hay argumentos
		{
			j = i + 4; // saltar espacios después de echo
			while (line[j] == ' ')
                j++;
            temp->arg = ft_strdup(line + j);
		}
        else
            temp->arg = ft_strdup(""); // Solo "echo" sin argumentos
    }
	else // inicializamos con valores seguros si no coincide
    {
        temp->command = ft_strdup("unknown");
        temp->command_arg = ft_strdup(line);
        temp->arg = ft_strdup("");
        temp->flag_built = 0;
    }
}

void pwd_com(t_com *temp, char *line)
{  // pwd_com modificada (ro)
    // printf("ha entrado a pwd\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "pwd", 3) == 0 && (line[i + 3] == ' ' || line[i + 3] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("pwd");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup(""); //ft_strdup(line + i + 4);
    }
	else // inicializamos con valores seguros si no coincide
    {
        temp->command = ft_strdup("unknown");
        temp->command_arg = ft_strdup(line);
        temp->arg = ft_strdup("");
        temp->flag_built = 0;
    }
}

void cd_com(t_com *temp, char *line)
{ // cd_com modificada (ro)
    // printf("ha entrado a cd\n");
    int i;
	int j;

	i = 0;
	j = 0;
    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "cd", 2) == 0 && (line[i + 2] == ' ' || line[i + 2] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("cd");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        if (line[i + 2] == ' ') // Si hay espacio después de "cd" significa que hay argumentos
		{
			j = i + 2; // saltar espacios después de cd
			while (line[j] == ' ')
                j++;
            temp->arg = ft_strdup(line + j);
		}
        else
            temp->arg = ft_strdup(""); // Solo "cd" sin argumentos
    }
	else // inicializamos con valores seguros si no coincide
    {
        temp->command = ft_strdup("unknown");
        temp->command_arg = ft_strdup(line);
        temp->arg = ft_strdup("");
        temp->flag_built = 0;
    }
}

void export_com(t_com *temp, char *line)
{ // gestiona el export para meter cada cosa en la estructura
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

void unset_com(t_com *temp, char *line)
{ // gestiona el unset para meter cada cosa en la estructura
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
