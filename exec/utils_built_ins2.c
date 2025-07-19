/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:04 by roo               #+#    #+#             */
/*   Updated: 2025/07/19 02:10:43 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_env_var(char *new_var, t_vars *vars)
{
    char *var_name;
    int existing_index;
    
    var_name = get_var_name(new_var); // Extraer nombre de variable
    existing_index = find_env_var(var_name, vars); // Buscar si ya existe
    if (existing_index >= 0) // Reemplazar variable existente
    {
        free(vars->env[existing_index]);
        vars->env[existing_index] = ft_strdup(new_var);
    }
    else // Añadir nueva variable
        add_new_env_vars(new_var, vars);
    
    free(var_name);
}

void add_new_env_vars(char *new_var, t_vars *vars)
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

int find_env_var(char *var_name, t_vars *vars)
{
    int i;
    int name_len;
    
    if (!var_name)
        return (-1);
    
    name_len = ft_strlen(var_name);
    i = 0;
    while (vars->env[i])
    {
        if (ft_strncmp(vars->env[i], var_name, name_len) == 0 && vars->env[i][name_len] == '=') // Comparar nombre y verificar que sigue '='
            return (i);  // Encontrada en posición i
        i++;
    }
    return (-1);  // No encontrada
}

char *get_var_name(char *var_assignment)
{
    char *equals_pos;
    
    equals_pos = ft_strchr(var_assignment, '=');
    if (!equals_pos)
        return (ft_strdup(var_assignment));  // Sin '=', todo es el nombre
    
    // Extraer solo la parte antes de '='
    return (ft_substr(var_assignment, 0, equals_pos - var_assignment));
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
