/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:57:33 by roo               #+#    #+#             */
/*   Updated: 2025/11/04 13:42:11 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_pipeline(t_com *list)
{
	t_com	*tmp_list;
	int		pipe_fd[2];

	tmp_list = list;
	while (tmp_list && tmp_list->next)
	{
		if (pipe(pipe_fd) == -1)
			return (write(2, "minishell: ", 11), perror("pipe"));
		if (tmp_list->fd_out == STDOUT_FILENO)
			tmp_list->fd_out = pipe_fd[WRITE_FD];
		else
			close(pipe_fd[WRITE_FD]);
		if (tmp_list->next->fd_in == STDIN_FILENO)
			tmp_list->next->fd_in = pipe_fd[READ_FD];
		else
			close(pipe_fd[READ_FD]);
		tmp_list = tmp_list->next;
	}
}

void	execute_pipeline(t_com *list)
{
	t_com	*tmp_list;
	pid_t	*pids;
	int		num_cmds;

	tmp_list = list;
	num_cmds = 0;
	while (tmp_list)
	{
		num_cmds++;
		tmp_list = tmp_list->next;
	}
	pids = malloc(sizeof(pid_t) * num_cmds);
	execute_pipelines2(list, pids);
	tmp_list = list;
	while (tmp_list)
	{
		clean_fds(tmp_list);
		tmp_list = tmp_list->next;
	}
	pipelines_signals(list, pids, num_cmds, 0);
	free(pids);
}

void	execute_pipelines2(t_com *list, pid_t *pids)
{
	t_com	*tmp_list;
	pid_t	pid;
	int		i;

	i = 0;
	tmp_list = list;
	while (tmp_list)
	{
		if (!tmp_list->redirects)
		{
			tmp_list->redirects = ft_calloc(1, sizeof(t_red));
			tmp_list->redirects->redirected = 0;
		}
		if (tmp_list->redirects->redirected != 1)
		{
			if (!redirections_control(tmp_list, 0, 0, 0))
			{
				tmp_list->redirects->redirected = 1;
				tmp_list = tmp_list->next;
				continue ;
			}
			tmp_list->redirects->redirected = 1;
		}
		pid = fork();
		if (pid == -1)
			return (write(2, "minishell: ", 11), ("fork"), free(pids));
		if (pid == 0)
			pids_pipelines(list, tmp_list);
		pids[i++] = pid;
		tmp_list = tmp_list->next;
	}
}

void	pipelines_signals(t_com *list, pid_t *pids, int num_cmds, int i)
{
	int		status;
	int		sig;

	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
			list->vars->exit_status = 130;
			else if (sig == SIGQUIT)
			{
				write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
				list->vars->exit_status = 131;
			}
			else
				list->vars->exit_status = 128 + sig;
		}
		else if (i == num_cmds - 1 && WIFEXITED(status))
			list->vars->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	pids_pipelines(t_com *list, t_com *tmp_list)
{
	setup_signals_default();
	apply_redirections(tmp_list);
	close_pipes(list, tmp_list);
	if (tmp_list->flag_built)
	{
		commands_control(tmp_list, tmp_list->vars);
		exit(0);
	}
	else
	{
		tmp_list->path_command = get_path(tmp_list->command, tmp_list->vars->env, tmp_list);
		if (!tmp_list->path_command)
		{
			ft_printf(2, "minishell: %s: command not found\n", tmp_list->command);
			exit(127);
		}
		if (execve(tmp_list->path_command, tmp_list->command_arg, tmp_list->vars->env) == -1)
		{
			write(2, "minishell: ", 11), 
			perror("execve");
			exit(127);
		}
	}
}

void	close_pipes(t_com *list, t_com *current_cmd)
{
	t_com	*tmp_list;

	tmp_list = list;
	while (tmp_list)
	{
		if (tmp_list != current_cmd)
		{
			if (tmp_list->fd_in != STDIN_FILENO)
				close(tmp_list->fd_in);
			if (tmp_list->fd_out != STDOUT_FILENO)
				close(tmp_list->fd_out);
		}
		tmp_list = tmp_list->next;
	}
}
