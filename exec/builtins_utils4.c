/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:42:05 by roo               #+#    #+#             */
/*   Updated: 2025/11/12 22:47:10 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (env_list->env_inf)
				free(env_list->env_inf);
			free(env_list);
			return ;
		}
		prev = env_list;
		env_list = env_list->next;
	}
}

int	export_var(t_vars *vars, char *var, int hidden)
{
	if (valid_var_name(var))
		add_update_env_var(vars, var, hidden);
	else
	{
		ft_printf(2, "export: '%s': not a valid identifier\n", var);
		return (0);
	}
	return (1);
}

int	number_in_range(char *str)
{
	int	sign;

	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (!ft_isdigit(*str))
		return (0);
	if (ft_strlen(str) > 19)
		return (0);
	if (ft_strlen(str) == 19)
	{
		if (sign == 1 && ft_strncmp(str, "9223372036854775807", 20) > 0)
			return (0);
		if (sign == -1 && ft_strncmp(str, "9223372036854775808", 20) > 0)
			return (0);
	}
	return (1);
}

int	is_variable_assignment(char *cmd)
{
	int		i;
	char	*equal_pos;
	char	*name;

	if (!cmd || !*cmd)
		return (0);
	equal_pos = ft_strchr(cmd, '=');
	if (!equal_pos || equal_pos == cmd)
		return (0);
	name = ft_substr(cmd, 0, equal_pos - cmd);
	if (!name)
		return (0);
	if (!valid_var_name(name))
		return (free(name), 0);
	i = equal_pos - cmd;
	while (i > 0 && cmd[i - 1] != ' ')
		i--;
	if (i != 0 && cmd[i - 1] == ' ')
		return (free(name), 0);
	return (free(name), 1);
}
