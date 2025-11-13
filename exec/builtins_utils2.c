/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/12 22:50:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_env_str(char *env_str, char **name, char **value)
{
	char	*equal_pos;

	equal_pos = ft_strchr(env_str, '=');
	if (equal_pos)
	{
		*name = ft_substr(env_str, 0, equal_pos - env_str);
		*value = ft_strdup(equal_pos + 1);
	}
	else
	{
		*name = ft_strdup(env_str);
		*value = NULL;
	}
}

t_env	*new_env_node(char *name, char *value, int hidden)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->env_name = name;
	new_var->env_inf = value;
	new_var->hidden = hidden;
	new_var->next = NULL;
	return (new_var);
}

t_env	*create_env_list(char *env_string)
{
	char	*name;
	char	*value;

	parse_env_str(env_string, &name, &value);
	return (new_env_node(name, value, 0));
}

static void	push_env_var(t_env **list, t_env *new)
{
	t_env	*node;

	node = *list;
	if (!node)
		*list = new;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

void	add_update_env_var(t_vars *vars, char *var_str, int hidden)
{
	char	*name;
	char	*value;
	t_env	*env;

	parse_env_str(var_str, &name, &value);
	env = find_env_var(vars, name);
	if (env)
	{
		free(env->env_inf);
		env->env_inf = value;
		free(name);
	}
	else
		push_env_var(&vars->env_list, new_env_node(name, value, hidden));
}
