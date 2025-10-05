/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:04 by roo               #+#    #+#             */
/*   Updated: 2025/10/05 19:33:25 by roo              ###   ########.fr       */
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
    if (equals_pos) // Extraer nombre y valor
    {
        name = ft_substr(var_str, 0, equals_pos - var_str);
        value = ft_strdup(equals_pos + 1);
		update_env(vars, name, value); // Actualizar el array de entorno
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

void update_env(t_vars *vars, char *name, char *value)
{
    int i = 0;
    char *var_entry;
    char *new_entry;
    
    new_entry = ft_strjoin(name, "=");
    new_entry = ft_strjoin_gnl(new_entry, value);
    while (vars->env[i]) // Buscar si ya existe en el array de entorno
    {
        var_entry = ft_substr(vars->env[i], 0, ft_strchr(vars->env[i], '=') - vars->env[i]);
        if (ft_strncmp(var_entry, name, ft_strlen(var_entry)) == 0) // Reemplazar la entrada existente
        {
            free(vars->env[i]);
            vars->env[i] = ft_strdup(new_entry);
            return(free(var_entry), free(new_entry));
        }
        free(var_entry);
        i++;
    }
    add_new_env_vars(new_entry, vars); // Si no encontrado, añade nueva entrada
    free(new_entry);
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

char *get_var_name(char *var_assignment)
{
    char *equals_pos;
    
    equals_pos = ft_strchr(var_assignment, '=');
    if (!equals_pos)
        return (ft_strdup(var_assignment));  // Sin '=', todo es el nombre
    return (ft_substr(var_assignment, 0, equals_pos - var_assignment)); // Extraer solo la parte antes de '='
}

int valid_var_name(char *var)
{
    int i;
    char *name;
    char *equals_pos;
    
	i = 0;
    equals_pos = ft_strchr(var, '=');
    if (equals_pos) // Extraer solo el nombre (antes del =)
        name = ft_substr(var, 0, equals_pos - var);
    else
        name = ft_strdup(var);
    if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z') || name[0] == '_')) // El primer carácter debe ser una letra o '_'
        return (free(name), 0);
    i = 1; // Los siguientes caracteres deben ser letras, números o '_'
    while (name[i]) 
    {
        if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9') || name[i] == '_')) 
            return (free(name), 0);
        i++;
    }
    return (free(name), 1);
}
