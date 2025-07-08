#include "../minishell.h"

void env_com(t_com *temp, char *line)
{ // MODIFICADA
    // printf("ha entrado a env\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "env", 3) == 0 && (line[i + 3] == ' ' || line[i + 3] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("env");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup("");
    }
	else // inicializamos con valores seguros si no coincide
    {
        temp->command = ft_strdup("unknown");
        temp->command_arg = ft_strdup(line);
        temp->arg = ft_strdup("");
        temp->flag_built = 0;
    }
}

void exit_com(t_com *temp, char *line)
{ // MODIFICADA
    // printf("ha entrado a exit\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "exit", 4) == 0 && (line[i + 4] == ' ' || line[i + 4] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("exit");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup("");
    }
	else // inicializamos con valores seguros si no coincide
    {
        temp->command = ft_strdup("unknown");
        temp->command_arg = ft_strdup(line);
        temp->arg = ft_strdup("");
        temp->flag_built = 0;
    }
}

void *not_built(t_com *temp, char *line)
{ // NO MODIFICADA
    // printf("ha entrado a not_built\n");
    int i = 0;

    while (line[i] == 32)
        i++;
    char **split = ft_split_mini(line + i, ' '); //hago un split por espacios
    temp->command = ft_strdup(split[0]); // ft_strdup para crear copias en lugar de split[0] directo
    temp->command_arg = ft_strdup(line + i);
    temp->arg = ft_strdup(line + i);
    temp->flag_built = 0;

	ft_free_free(split); // free para liberar el split que ya no necesitamos
}
