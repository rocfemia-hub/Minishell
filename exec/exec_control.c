/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:51:09 by roo               #+#    #+#             */
/*   Updated: 2025/11/09 14:06:42 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_fds(t_com *list)
{
	if (list->fd_in != STDIN_FILENO)
		close(list->fd_in);
	if (list->fd_out != STDOUT_FILENO)
		close(list->fd_out);
	list->fd_in = STDIN_FILENO;
	list->fd_out = STDOUT_FILENO;
	if (list->redirects && list->redirects->heredoc_file)
	{
		unlink(list->redirects->heredoc_file);
		free(list->redirects->heredoc_file);
		list->redirects->heredoc_file = NULL;
	}
}

void	execute_control(t_com *list, t_vars *vars)
{
	setup_signals_noninteractive();
	if (list && list->redirects)
		list->redirects->redirected = 0;
	list = list;
	if (list)
	{
		if (list->next == NULL)
		{
			if (!redirections_control(list, 0, 0, 0))
				return (vars->exit_status = 1, clean_fds(list));
			if (!list->command || ft_strlen(list->command) == 0)
				return (ft_printf(2, "minishell: : command not found\n"),
					vars->exit_status = 127, clean_fds(list));
			if (list->flag_built == 1)
				commands_control(list, vars);
			else
				execute(list, vars);
			clean_fds(list);
		}
		else
			(setup_pipeline(list), execute_pipeline(list));
	}
}

static int	builtins_control(t_com *list, t_vars *vars)
{
	if (ft_strnstr(list->command, "echo", 5))
		return (echo_function(list, vars), 1);
	else if (ft_strnstr(list->command, "pwd", 4))
		return (pwd_function(list, vars), 1);
	else if (ft_strnstr(list->command, "exit", 5))
		return (exit_function(list, vars), 1);
	else if (ft_strnstr(list->command, "env", 4))
		return (env_function(list, vars), 1);
	else if (ft_strnstr(list->command, "cd", 3))
		return (cd_function(list, vars, NULL), 1);
	else if (ft_strnstr(list->command, "export", 7))
		return (export_function(list, vars), 1);
	else if (ft_strnstr(list->command, "unset", 6))
		return (unset_function(list, vars), 1);
	return (0);
}

void	commands_control(t_com *list, t_vars *vars)
{
	if (!list || !list->command)
		return ;
	if (!redirections_control(list, 0, 0, 0))
		return ;
	if (list->flag_built == 1)
	{
		if (!builtins_control(list, vars))
			return (ft_printf(2, "minishell: %s: command not found\n",
					list->command), vars->exit_status = 127, (void)0);
		clean_fds(list);
	}
	else
		execute(list, vars);
}

int	redirections_control(t_com *list, int j, int q, int k)
{
	int	i;

	i = -1;
	if (list->redirects == NULL)
		return (0);
	if (list->redirects->redirected == 1)
		return (1);
	list->redirects->redirected = 1;
	if (list->redirects->redirect_heredoc)
	{
		heredoc_execution(list);
		if (g_signal == SIGINT)
			return (0);
		return (1);
	}
	while (list->redirects->t_red && list->redirects->t_red[++i] != 0)
	{
		if (list->redirects->t_red[i] == 1 && !infile_redirection(list, j++))
			return (0);
		if (list->redirects->t_red[i] == 2 && !outfile_redirection(list, q++))
			return (0);
		if (list->redirects->t_red[i] == 3 && !append_redirection(list, k++))
			return (0);
	}
	return (1);
}
