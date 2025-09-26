/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:04 by roo               #+#    #+#             */
/*   Updated: 2025/09/26 18:12:40 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_update_env_var(t_vars *vars, char *var_str)
{
    char *equals_pos;
    char *name;
    char *value;
    t_env *env_list;

    equals_pos = ft_strchr(var_str, '=');
    if (equals_pos)
    {
        name = ft_substr(var_str, 0, equals_pos - var_str);
        value = ft_strdup(equals_pos + 1);
    }
    else
    {
        name = ft_strdup(var_str);
        value = ft_strdup("");
    }
    env_list = find_env_var(vars, name); // Buscar si ya existe
    if (env_list) // Actualizar valor existente
    {
        free(env_list->env_inf);
        env_list->env_inf = value;
        free(name);
    }
    else
        add_env_var_to_list(vars, name, value); // Añadir nueva variable
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

int find_env_var(t_vars *vars, char *var_name)
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
    return (ft_substr(var_assignment, 0, equals_pos - var_assignment)); // Extraer solo la parte antes de '='
}
