/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:57:33 by roo               #+#    #+#             */
/*   Updated: 2025/11/11 18:37:02 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_pipelines2(t_com *list, pid_t *pids)
{
	t_com	*tmp_list;
	int		i;

	tmp_list = list;
	i = 0;
	while (tmp_list)
	{
		if (!redirections_control(tmp_list, 0, 0, 0))
		{
			pids[i] = fork();
			if (pids[i++] == 0)
				exit(1);
			if (tmp_list->fd_in != STDIN_FILENO)
				close(tmp_list->fd_in);
			if (tmp_list->fd_out != STDOUT_FILENO)
				close(tmp_list->fd_out);
			tmp_list = tmp_list->next;
			continue ;
		}
		pids_pipelines(list, tmp_list, pids, i++);
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
	if (!pids)
		return ;
	ft_bzero(pids, sizeof(pid_t) * num_cmds);
	execute_pipelines2(list, pids);
	if (num_cmds > 0 && pids[0] > 0)
		tcsetpgrp(STDIN_FILENO, pids[0]);
	pipelines_signals(list, pids, num_cmds, 0);
	tcsetpgrp(STDIN_FILENO, getpid());
	free(pids);
}

void	setup_pipeline(t_com *list)
{
	int	pipe_fd[2];

	while (list && list->next)
	{
		if (pipe(pipe_fd) == -1)
			return (write(2, "minishell: ", 11), perror("pipe"));
		if (list->fd_out == STDOUT_FILENO)
			list->fd_out = pipe_fd[WRITE_FD];
		else
			close(pipe_fd[WRITE_FD]);
		if (list->next->fd_in == STDIN_FILENO)
			list->next->fd_in = pipe_fd[READ_FD];
		else
			close(pipe_fd[READ_FD]);
		list = list->next;
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
