/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 13:42:52 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_function(t_com *list, t_vars *vars)
{
	t_env	*env_list;
	char	*line;

	if (list->args && list->args[0])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(list->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (vars->exit_status = 127, (void)0);
	}
	if (!vars->env_list)
		return (vars->exit_status = 0, (void)0);
	env_list = vars->env_list;
	while (env_list)
	{
		line = ft_strjoin(env_list->env_name, "=");
		line = ft_strjoin_gnl(line, env_list->env_inf);
		write(list->fd_out, line, ft_strlen(line));
		write(list->fd_out, "\n", 1);
		free(line);
		env_list = env_list->next;
	}
	vars->exit_status = 0;
}

void	export_function(t_com *list, t_vars *vars)
{
	int	i;
	int	has_error;

	i = 0;
	has_error = 0;
	if (!list->args || !*list->args)
		return (free(list->args), (list->args = NULL),
			print_export_vars(list, vars));
	while (list->args && list->args[i])
	{
		if (!valid_var_name(list->args[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(list->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			has_error = 1;
		}
		else
			add_update_env_var(vars, list->args[i]);
		i++;
	}
	ft_free_free(list->args);
	list->args = NULL;
	if (has_error)
		vars->exit_status = 1;
	else
		vars->exit_status = 0;
}

void	unset_function(t_com *list, t_vars *vars)
{
	int	i;
	int	has_error;

	i = 0;
	has_error = 0;
	if (!list->args || !*list->args)
		return (vars->exit_status = 0, (void)0);
	while (list->args[i])
	{
		if (valid_var_name(list->args[i]))
			remove_env_var(vars, list->args[i]);
		else
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(list->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			has_error = 1;
		}
		i++;
	}
	ft_free_free(list->args);
	list->args = NULL;
	if (has_error)
		vars->exit_status = 1;
	else
		vars->exit_status = 0;
}
