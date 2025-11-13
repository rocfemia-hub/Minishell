/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/11/12 22:50:55 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_function(t_com *list, t_vars *vars)
{
	t_env	*env_list;

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
		if (!env_list->hidden && env_list->env_inf)
			print_env_var(list, env_list);
		env_list = env_list->next;
	}
	vars->exit_status = 0;
}

void	export_function(t_com *list, t_vars *vars)
{
	int	i;

	i = -1;
	if (list->command && is_variable_assignment(list->command))
	{
		if (!export_var(vars, list->command, 1))
			vars->exit_status = 1;
		return ;
	}
	if (!list->args || !*list->args)
		return (free(list->args), (list->args = NULL),
			print_export_vars(list, vars));
	while (list->args && list->args[++i])
	{
		if (!export_var(vars, list->args[i], 0))
			vars->exit_status = 1;
	}
	ft_free_free(list->args);
	list->args = NULL;
}

void	unset_function(t_com *list, t_vars *vars)
{
	int	i;

	i = 0;
	if (!list->args || !*list->args)
		return (vars->exit_status = 0, (void)0);
	while (list->args[i])
	{
		if (valid_var_name(list->args[i]))
			remove_env_var(vars, list->args[i]);
		i++;
	}
	ft_free_free(list->args);
	list->args = NULL;
}
