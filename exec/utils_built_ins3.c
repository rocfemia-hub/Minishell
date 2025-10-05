/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:34 by roo               #+#    #+#             */
/*   Updated: 2025/10/05 20:01:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_to_list(t_vars *vars, char **env)
{
	int i;
    t_env *new_var;
    t_env *env_list;
    
    i = 0;
    vars->env_list = NULL;
    while (env[i])
    {
		new_var = create_env_list(env[i]);
        if (!vars->env_list)
		vars->env_list = new_var;
        else
        {
			env_list = vars->env_list;
            while (env_list->next)
			env_list = env_list->next;
            env_list->next = new_var;
        }
        i++;
    }
}

t_env *create_env_list(char *env_string)
{
	t_env *new_var;
	char *equals_pos;
	
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	
	equals_pos = ft_strchr(env_string, '=');
	if (equals_pos)
	{
		new_var->env_name = ft_substr(env_string, 0, equals_pos - env_string);
		new_var->env_inf = ft_strdup(equals_pos + 1);
	}
	else
	{
		new_var->env_name = ft_strdup(env_string);
		new_var->env_inf = ft_strdup("");
	}
	new_var->next = NULL;
	return (new_var);
}

void add_env_var_to_list(t_vars *vars, char *name, char *value)
{
    t_env *new_var;
    t_env *env_list;

    new_var = malloc(sizeof(t_env));
    new_var->env_name = name;
    new_var->env_inf = value;
    new_var->next = NULL;

    if (!vars->env_list)
        vars->env_list = new_var;
    else
    {
        env_list = vars->env_list;
        while (env_list->next)
            env_list = env_list->next;
        env_list->next = new_var;
    }
}

t_env *find_env_var(t_vars *vars, char *env_name)
{
    t_env *env_list = vars->env_list;
    
    while (env_list)
    {
        if (ft_strncmp(env_list->env_name, env_name, ft_strlen(env_list->env_name)) == 0)
            return (env_list);
        env_list = env_list->next;
    }
    return (NULL);
}

void remove_in_env_array(t_vars *vars, char *name)
{// Elimina del array de entorno
    int i;
    int j;
    char *var_name;
	char *equals_pos;
    
	i = 0;
    while (vars->env[i])
    {
        equals_pos = ft_strchr(vars->env[i], '='); // Extraer el nombre de variable de "NOMBRE=VALOR"
        if (equals_pos)
            var_name = ft_substr(vars->env[i], 0, equals_pos - vars->env[i]);
        else
            var_name = ft_strdup(vars->env[i]);
        if (ft_strncmp(var_name, name, ft_strlen(var_name)) == 0) // Si encontramos la variable, se elimina
        {
            free(vars->env[i]);
            j = i; // Mover todas las entradas siguientes una posición hacia arriba
            while (vars->env[j + 1])
            {
                vars->env[j] = vars->env[j + 1];
                j++;
            }
            return(vars->env[j] = NULL, free(var_name));
        }
        free(var_name);
        i++;
    }
}

/*char *get_env_value(t_vars *vars, char *env_name)
{
    t_env *var = find_env_var(vars, env_name);
    
    if (var)
        return (var->env_inf);
    return (NULL);
}*/
