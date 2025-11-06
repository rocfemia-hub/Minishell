/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 18:21:58 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_var_name(char *var_assignment)
{
	char	*equals_pos;

	equals_pos = ft_strchr(var_assignment, '=');
	if (!equals_pos)
		return (ft_strdup(var_assignment));
	return (ft_substr(var_assignment, 0, equals_pos - var_assignment));
}

int	valid_var_name(char *var)
{
	char	*equals_pos;
	char	*name;
	int		i;

	i = 0;
	equals_pos = ft_strchr(var, '=');
	if (equals_pos)
		name = ft_substr(var, 0, equals_pos - var);
	else
		name = ft_strdup(var);
	if (!((name[0] >= 'a' && name[0] <= 'z')
			|| (name[0] >= 'A' && name[0] <= 'Z') || name[0] == '_'))
		return (free(name), 0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9') || name[i] == '_'))
			return (free(name), 0);
		i++;
	}
	return (free(name), 1);
}
