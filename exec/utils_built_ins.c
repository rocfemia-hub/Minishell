#include "../minishell.h"

int valid_n_option(char *str)
{
    int i;
    
    if (!str || str[0] != '-' || !str[1])
        return (0);
    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int valid_number(char *str)
{
    int i = 0;
    
    if (!str || !*str)
        return (0);
    while (str[i] == ' ') // Saltar espacios iniciales
        i++;
    if (str[i] == '+' || str[i] == '-') // Permitir signo opcional
        i++;
    if (!str[i]) // Debe haber al menos un dígito después del signo
        return (0);
    while (str[i]) // Verificar que todos los caracteres restantes sean dígitos
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    
    return (1);
}

void add_env_vars(char *new_var, t_vars *vars)
{
    char **new_env;
    int env_count; 
    int i;
    
	i = 0;
    env_count = 0; // Contar variables actuales
    while (vars->env[env_count]) // Incrementar hasta encontrar NULL
        env_count++;
    new_env = malloc(sizeof(char *) * (env_count + 2)); // Crear nuevo array
    if (!new_env)
        return;
    while (i < env_count) // Copiar variables existentes
    {
        new_env[i] = vars->env[i]; // Solo copia PUNTEROS, no duplica strings
        i++;
    }
    new_env[i] = ft_strdup(new_var); // Añadir nueva variable
    new_env[i + 1] = NULL; // Terminar el array con NULL
    vars->env = new_env; // Reemplazar el array antiguo con el nuevo
}

void print_export_vars(t_com *list, t_vars *vars)
{
    int i;
    
    i = 0;
    while (vars->env[i])
    {
        write(list->fd_out, "declare -x ", 11); // Escribir prefijo estándar de bash para variables exportadas
        write(list->fd_out, vars->env[i], ft_strlen(vars->env[i])); // Escribir la variable completa (formato: VAR=valor)
        write(list->fd_out, "\n", 1); // Añadir salto de línea después de cada variable
        i++;
    }
}
