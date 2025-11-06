/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:33 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 13:23:18 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_function(t_com *list, t_vars *vars)
{
	int	i;
	int	newline;

	if (!list->args || !*list->args)
	{
		write(list->fd_out, "\n", 1);
		list->vars->exit_status = 0;
		return ;
	}
	i = -1;
	newline = 1;
	while (list->args[++i] && valid_n_option(list->args[i]))
		newline = 0;
	while (list->args[i])
	{
		write(list->fd_out, list->args[i], ft_strlen(list->args[i]));
		if (list->args[i + 1])
			write(list->fd_out, " ", 1);
		i++;
	}
	if (newline && vars)
		write(list->fd_out, "\n", 1);
	list->vars->exit_status = 0;
}

void	pwd_function(t_com *list, t_vars *vars)
{
	ssize_t	bytes_written;

	if (vars->pwd == NULL)
		return (vars->exit_status = 1, write(2, "minishell: ", 11), perror("pwd"));
	bytes_written = write(list->fd_out, vars->pwd, ft_strlen(vars->pwd));
	if (bytes_written != -1)
		write(list->fd_out, "\n", 1);
	vars->exit_status = 0;
}

void	exit_function(t_com *list, t_vars *vars)
{
	if (!list->args[0] || !vars)
		exit(0);
	if (list->args[0] && !list->args[1])
	{
		if (valid_number(list->args[0]))
			exit(ft_atoi(list->args[0]));
		else
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(2);
		}
	}
	write(2, "exit: too many arguments\n", 25);
	return (vars->exit_status = 1, (void)0);
}

void	cd_function(t_com *list, t_vars *vars)
{
	char	*target_dir;

	if (!list->args || !list->args[0])
	{
		target_dir = get_env_var(vars, "HOME");
		if (!target_dir)
			return (vars->exit_status = 1, write(2, "cd: HOME not set\n", 17), (void)0);
	}
	else if (list->args[0]) // && !list->args[1]
		target_dir = list->args[0];
	else
		return (vars->exit_status = 1, write(2, "cd: too many arguments\n", 23), (void)0);
	if (chdir(target_dir) == -1)
	{
		if (errno == EACCES)
			write(2, "minishell: cd: Permission denied\n", 33);
		else if (errno == ENOENT)
			write(2, "minishell: cd: No such file or directory\n", 41);
		else
			write(2, "minishell: cd: Error changing directory\n", 40);
		return (vars->exit_status = 1, (void)0);
	}
	if (!cd_aux_funcion(list, vars))
		return (vars->exit_status = 1, (void)0);
	vars->exit_status = 0;
}
