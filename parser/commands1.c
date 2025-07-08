#include "../minishell.h"

void echo_com(t_com *temp, char *line)
{ // MODIFICADA
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
        temp->command_arg = ft_strdup(line + i); // (line + i) significa "dame un puntero al carácter que está en la posición i de la cadena"
        if (line[i + 4] == ' ') // Si hay espacio después de "echo" significa que hay argumentos
		{
			j = i + 4; // saltar espacios después de echo
			while (line[j] == ' ')
                j++;
            temp->arg = ft_strdup(line + j); // (line + j) significa "dame un puntero al carácter que está en la posición j de la cadena"
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
{ // MODIFICADA
    // printf("ha entrado a pwd\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "pwd", 3) == 0 && (line[i + 3] == ' ' || line[i + 3] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("pwd");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i); // (line + i) significa "dame un puntero al carácter que está en la posición i de la cadena"
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

void cd_com(t_com *temp, char *line)
{ // MODIFICADA
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
        temp->command_arg = ft_strdup(line + i); // (line + i) significa "dame un puntero al carácter que está en la posición i de la cadena"
        if (line[i + 2] == ' ') // Si hay espacio después de "cd" significa que hay argumentos
		{
			j = i + 2; // saltar espacios después de cd
			while (line[j] == ' ')
                j++;
            temp->arg = ft_strdup(line + j); // (line + j) significa "dame un puntero al carácter que está en la posición j de la cadena"
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
{ // MODIFICADA
    // printf("ha entrado a export\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "export", 6) == 0 && (line[i + 6] == ' ' || line[i + 6] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("export");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i); // (line + i) significa "dame un puntero al carácter que está en la posición i de la cadena"
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

void unset_com(t_com *temp, char *line)
{ // MODIFICADA
    // printf("ha entrado a unset\n");
    int i = 0;

    while (line[i] == 32) // para saltar los espacios al principio
        i++;
    if (ft_strncmp(line + i, "unset", 5) == 0 && (line[i + 5] == ' ' || line[i + 5] == '\0')) // debe haber espacio o ser el final de la string
    {
        temp->command = ft_strdup("unset");
        temp->flag_built = 1;
        temp->command_arg = ft_strdup(line + i); // (line + i) significa "dame un puntero al carácter que está en la posición i de la cadena"
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
