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
{
    int i = 0;
    int j = 0; // longitud del comando

    while (line[i] && line[i] == ' ') //salta los espacios
        i++;
    while (line[i + j] && line[i + j] != ' ') // me llega al final del comando
        j++;
    temp->command = ft_substr(line, i, j); // compia el comando (empieza en i y la longitud del comando que es j)
    i += j; // me avanza hasta el final del comando
    while (line[i] == ' ')
        i++; // me salta los espacios
    if (line[i]) // me copia en arg el resto de linea, sin el comando
        temp->arg = ft_strdup(line + i);
    temp->command_arg = ft_strdup(line); // me copia toda la linea
    temp->flag_built = 0; // no es un built
    return (NULL);
}
