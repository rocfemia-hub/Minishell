/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:53:54 by roo               #+#    #+#             */
/*   Updated: 2025/11/21 14:26:57 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pids_funcion(t_com *list, int status)
{
	int		pid;
	char	**env;

	env = list_to_env(list->vars->env_list);
	pid = fork();
	if (pid == -1)
		return (write(2, "minishell: ", 11), perror("fork"), 0);
	if (pid == 0)
	{
		setup_signals_default();
		apply_redirections(list);
		if (execve(list->path_command, list->command_arg, env) == 0)
		{
			write(2, "minishell: ", 11);
			perror("execve");
			list->vars->exit_status = 127;
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	execute_signals(list, status);
	ft_free_free(env);
	return (1);
}

static void	pids2_pipelines(t_com *list, t_com *tmp_list)
{
	setup_signals_default();
	apply_redirections(tmp_list);
	close_pipes(list, tmp_list);
	if (tmp_list->flag_built)
	{
		commands_control(tmp_list, tmp_list->vars);
		exit(tmp_list->vars->exit_status);
	}
	else
	{
		tmp_list->path_command = get_path(tmp_list->command, tmp_list->vars);
		if (!tmp_list->path_command)
		{
			ft_printf(2, "minishell: %s: command not found\n",
				tmp_list->command);
			exit(127);
		}
		if (execve(tmp_list->path_command, tmp_list->command_arg,
				list_to_env(tmp_list->vars->env_list)) == -1)
		{
			(write(2, "minishell: ", 11), perror("execve"));
			exit(127);
		}
	}
}

void	pids_pipelines(t_com *list, t_com *tmp_list, pid_t *pids, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (write(2, "minishell: ", 11), perror("fork"), free(pids));
	if (pid == 0)
		pids2_pipelines(list, tmp_list);
	else
	{
		if (tmp_list->fd_in != STDIN_FILENO)
			close(tmp_list->fd_in);
		if (tmp_list->fd_out != STDOUT_FILENO)
			close(tmp_list->fd_out);
		pids[i] = pid;
	}
}
