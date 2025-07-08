#include "../minishell.h"

void echo_com(t_com *temp, char *line, char *cmd)
{
	int i;
    char quote;

    i = 0;
	if (ft_strncmp(cmd, "echo", 4))
		return;
	temp->command = ft_strdup("echo");
	temp->flag_built = 1;
	temp->command_arg = ft_strdup(line);
	while (line[i] == ' ')
		i++;
	if (line[i] == '"' || line[i] == '\'') 	// Saltar el comando, teniendo en cuenta si viene con comillas
	{
		quote = line[i++];
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] == quote)
			i++; // salto la comilla de cierre
	}
	else
		while (line[i] && line[i] != ' ')
			i++; // salto el comando normal
	while (line[i] == ' ') 	// Saltar espacios antes del argumento
		i++;
	if (line[i]) 	// Guardar el argumento (si hay)
		temp->arg = ft_strdup(line + i);
	else
		temp->arg = ft_strdup("");
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
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup("");
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
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup("");
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
        temp->command_arg = ft_strdup(line + i);
        temp->arg = ft_strdup("");
    }
}
