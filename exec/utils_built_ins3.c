/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:34 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:54:12 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_to_list(t_vars *vars, char **env)
{
	int i;
    t_env *new_var;
    t_env *current;
    
    i = 0;
    vars->env_list = NULL;
    while (env[i])
    {
		new_var = create_env_list(env[i]);
        if (!vars->env_list)
		vars->env_list = new_var;
        else
        {
			current = vars->env_list;
            while (current->next)
			current = current->next;
            current->next = new_var;
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

/*t_env *find_env_var(t_vars *vars, char *env_name)
{
    t_env *current = vars->env_list;
    
    while (current)
    {
        if (ft_strcmp(current->env_name, env_name) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

char *get_env_value(t_vars *vars, char *env_name)
{
    t_env *var = find_env_var(vars, env_name);
    
    if (var)
        return (var->env_inf);
    return (NULL);
}*/
