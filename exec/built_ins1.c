/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:33 by roo               #+#    #+#             */
/*   Updated: 2025/11/02 13:42:19 by roo              ###   ########.fr       */
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
		return;
	}
	i = 0;
	newline = 1;
	while (list->args[i] && valid_n_option(list->args[i]))
	{
		newline = 0;
		i++;
	}
	while (list->args[i])
	{
		write(list->fd_out, list->args[i], ft_strlen(list->args[i]));
		if (list->args[i + 1])
			write(list->fd_out, " ", 1);
		i++;
	}
	if (newline)
		write(list->fd_out, "\n", 1);
	list->vars->exit_status = 0;
}

void	pwd_function(t_com *list, t_vars *vars)
{
	char	cwd[1024];
	ssize_t	bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (write(2, "minishell: ", 11), perror("pwd"));
	bytes_written = write(list->fd_out, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(list->fd_out, "\n", 1);
	vars->exit_status = 0;
}

void	exit_function(t_com *list, t_vars *vars)
{
	if (!list->args[0])
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
}

void	cd_function(t_com *list, t_vars *vars)
{
	char	*target_dir;
	char	*current_dir;
	char	*old_pwd;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (write(2, "minishell: ", 11), perror("cd"));
	if (!list->args || !list->args[0])
		if (!getenv("HOME"))
			return (write(2, "cd: HOME not set\n", 17), free(current_dir));
	else if (list->args [1])
	{
		write(2, "cd: too many arguments\n", 23);
		return (ft_free_free(list->args));
	}
	target_dir = list->args[0];
	if (chdir(target_dir) == -1)
	{
		write(2, "cd: ", 4);
		write(2, target_dir, ft_strlen(target_dir));
		write(2, ": No such file or directory\n", 28);
		return (free(target_dir));
	}
	old_pwd = ft_strjoin("OLDPWD=", current_dir);
	cd_aux_funcion(list, vars, old_pwd);
	vars->exit_status = 0;
}
