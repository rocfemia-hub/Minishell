/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:39:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 00:51:13 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	aux_pipe_signal(t_com *list, int status, int i, int num_cmds)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			list->vars->exit_status = 130;
		}
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
}

void	pipelines_signals(t_com *list, pid_t *pids, int num_cmds, int i)
{
	int		status;

	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		aux_pipe_signal(list, status, i, num_cmds);
		i++;
	}
}

void	setup_signals_default(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_noninteractive(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
