/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:29 by roo               #+#    #+#             */
/*   Updated: 2025/11/12 01:50:47 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_n_option(char *str)
{
	int	i;

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

int	valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
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

int	cd_aux_funcion(t_com *list, t_vars *vars)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (write(2, "minishell: ", 11), perror("cd"), 0);
	old_pwd = ft_strjoin("OLDPWD=", vars->pwd);
	add_update_env_var(vars, old_pwd, 0);
	free(old_pwd);
	if (vars->pwd)
		free(vars->pwd);
	vars->pwd = current_dir;
	new_pwd = ft_strjoin("PWD=", vars->pwd);
	add_update_env_var(vars, new_pwd, 0);
	free(new_pwd);
	if (list->args)
	{
		ft_free_free(list->args);
		list->args = NULL;
	}
	return (vars->exit_status = 0, 1);
}

void	print_export_vars(t_com *list, t_vars *vars)
{
	t_env	*env_list;

	env_list = vars->env_list;
	while (env_list)
	{
		if (!env_list->hidden)
		{
			if (!env_list->env_inf)
				ft_printf(list->fd_out, "declare -x %s\n", env_list->env_name);
			else
				ft_printf(list->fd_out, "declare -x %s=\"%s\"\n",
					env_list->env_name, env_list->env_inf);
		}
		env_list = env_list->next;
	}
	vars->exit_status = 0;
}
