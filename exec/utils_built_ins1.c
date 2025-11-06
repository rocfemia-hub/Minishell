/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:29 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 18:14:43 by roo              ###   ########.fr       */
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

void	print_export_vars(t_com *list, t_vars *vars)
{
	t_env	*env_list;
	char	*line;
	char	*tmp_line;

	env_list = vars->env_list;
	while (env_list)
	{
		write(list->fd_out, "declare -x ", 11);
		if (ft_strlen(env_list->env_inf) != 0)
			tmp_line = ft_strjoin(env_list->env_name, "=");
		else
			tmp_line = ft_strdup(env_list->env_name);
		line = ft_strjoin(tmp_line, env_list->env_inf);
		free(tmp_line);
		write(list->fd_out, line, ft_strlen(line));
		write(list->fd_out, "\n", 1);
		free(line);
		env_list = env_list->next;
	}
	vars->exit_status = 0;
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

int	cd_aux_funcion(t_com *list, t_vars *vars)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (write(2, "minishell: ", 11), perror("cd"), 0);
	old_pwd = ft_strjoin("OLDPWD=", vars->pwd);
	add_update_env_var(vars, old_pwd);
	free(old_pwd);
	if (vars->pwd)
		free(vars->pwd);
	vars->pwd = current_dir;
	new_pwd = ft_strjoin("PWD=", vars->pwd);
	add_update_env_var(vars, new_pwd);
	free(new_pwd);
	if (list->args)
	{
		ft_free_free(list->args);
		list->args = NULL;
	}
	return (vars->exit_status = 0, 1);
}
