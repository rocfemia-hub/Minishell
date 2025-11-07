/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/07 19:25:51 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

static void	init_env(t_vars *vars)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	add_update_env_var(vars, ft_strjoin("PWD=", cwd));
	add_update_env_var(vars, ft_strdup("SHLVL=1"));
	add_update_env_var(vars, ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin"));
	add_update_env_var(vars, ft_strdup("_=/usr/bin/env"));
}

static void	init_vars(t_vars *vars, char **env)
{
	t_env	*minishell_on;

	vars->exit_status = 0;
	vars->pwd = getcwd(NULL, 0);
	if (!env || !env[0])
		init_env(vars);
	else
	{
		env_to_list(vars, env);
		minishell_on = find_env_var(vars, "MINISHELL_ACTIVE");
		if (minishell_on)
			increment_shlvl(vars);
		else
		{
			add_update_env_var(vars, ft_strdup("SHLVL=1"));
			add_update_env_var(vars, ft_strdup("MINISHELL_ACTIVE=1"));
		}
	}
}

static void	init_fds(t_com *list, t_vars *vars)
{
	while (list)
	{
		list->fd_in = STDIN_FILENO;
		list->fd_out = STDOUT_FILENO;
		list->vars = vars;
		if (list->next)
			list->flag_pipe = 1;
		list = list->next;
	}
}

static int	gestion_line(t_com **commands, t_vars *vars)
{
	char	*line;

	g_signal = 0;
	line = readline("minishell-> ");
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	if (g_signal == SIGINT)
	{
		vars->exit_status = 130;
		g_signal = 0;
	}
	if (line[0] == '\0')
		return (free(line), 0);
	add_history(line);
	if (!line_break(line))
		return (free(line), 0);
	*commands = token(line, vars);
	free(line);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_com	*commands;
	t_vars	vars;

	if (argc < 1 && !argv)
		return (1);
	commands = NULL;
	ft_bzero(&vars, sizeof(vars));
	init_vars(&vars, env);
	setup_signals_interactive();
	while (1)
	{
		if (!gestion_line(&commands, &vars))
			continue ;
		init_fds(commands, &vars);
		setup_pipeline(commands);
		execute_control(commands, &vars);
		setup_signals_interactive();
		if (g_signal == SIGINT)
			vars.exit_status = 130;
		free_t_com_list(commands);
		commands = NULL;
	}
	free(vars.pwd);
	return (0);
}
