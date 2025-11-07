/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/07 19:46:36 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_list(char *env_string)
{
	t_env	*new_var;
	char	*equals_pos;

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

t_env	*find_env_var(t_vars *vars, char *env_name)
{
	t_env	*env_list;

	env_list = vars->env_list;
	while (env_list)
	{
		if (ft_strncmp(env_list->env_name, env_name,
				ft_strlen(env_list->env_name)) == 0)
		{
			if (ft_strlen(env_list->env_name) == ft_strlen(env_name))
				return (env_list);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

static void	add_env_var_to_list(t_vars *vars, char *name, char *value)
{
	t_env	*new_var;
	t_env	*env_list;

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

void	add_update_env_var(t_vars *vars, char *var_str)
{
	char	*equals_pos;
	char	*name;
	char	*value;
	t_env	*env_list;

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
	env_list = find_env_var(vars, name);
	if (env_list)
	{
		free(env_list->env_inf);
		env_list->env_inf = value;
		free(name);
	}
	else
		add_env_var_to_list(vars, name, value);
}

void	remove_env_var(t_vars *vars, char *name)
{
	t_env	*env_list;
	t_env	*prev;

	env_list = vars->env_list;
	prev = NULL;
	while (env_list)
	{
		if (ft_strncmp(env_list->env_name, name,
				ft_strlen(env_list->env_name)) == 0)
		{
			if (prev)
				prev->next = env_list->next;
			else
				vars->env_list = env_list->next;
			free(env_list->env_name);
			free(env_list->env_inf);
			free(env_list);
			return ;
		}
		prev = env_list;
		env_list = env_list->next;
	}
}
