/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/10/31 13:34:19 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_control(t_com *list, t_vars *vars)
{
	t_com	*tmp_list;

	//setup_signals_noninteractive(); // Configurar señales para ejecución de comandos
	list->redirects->redirected = 0;
	tmp_list = list;
	if (tmp_list->next == NULL)
	{
		if (!redirections_control(tmp_list, 0, 0, 0))
		{
			vars->exit_status = 1;
			return (clean_fds(tmp_list));
		}
		if (tmp_list->flag_built == 1)
			commands_control(tmp_list, vars);
		else
			execute(tmp_list, vars);
		clean_fds(tmp_list);
	}
	else
	{
		setup_pipeline(list);
		execute_pipeline(list);
	}
}

void	commands_control(t_com *list, t_vars *vars)
{
	if (!list || !list->command)
		return ;
	if (!redirections_control(list, 0, 0, 0))
		return ;
	if (list->flag_built == 1)
	{
		if (ft_strnstr(list->command, "echo", 5))
			echo_function(list, vars);
		else if (ft_strnstr(list->command, "pwd", 4))
			pwd_function(list, vars);
		else if (ft_strnstr(list->command, "exit", 5))
			exit_function(list, vars);
		else if (ft_strnstr(list->command, "env", 4))
			env_function(list, vars);
		else if (ft_strnstr(list->command, "cd", 3))
			cd_function(list, vars);
		else if (ft_strnstr(list->command, "export", 7))
			export_function(list, vars);
		else if (ft_strnstr(list->command, "unset", 6))
			unset_function(list, vars);
		clean_fds(list);
	}
	else
		execute(list, vars);
}

char	*get_path(char *cmd, char **envp, t_com *pipex)
{
	char	**paths;
	char	*result;

	if ((!cmd) || access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	pipex->i = -1;
	while (envp[++pipex->i])
		if (ft_strncmp(envp[pipex->i], "PATH=", 5) == 0)
			break ;
	if (envp[pipex->i] == NULL)
		return (NULL);
	paths = ft_split(&envp[pipex->i][5], ':');
	pipex->i = -1;
	while (paths[++pipex->i])
	{
		result = ft_strjoin(paths[pipex->i], "/");
		result = ft_strjoin_gnl(result, cmd);
		if (access(result, X_OK) == 0)
			break ;
		free(result);
		result = NULL;
	}
	if (result == NULL)
		return (result);
	return (ft_free_free(paths), result);
}

int	execute(t_com *list, t_vars *vars)
{
	int	status;

	list->path_command = get_path(list->command, list->vars->env, list);
	if (list->command)
	{
		if (ft_strnstr(list->command, ";", ft_strlen(list->command)))
		{
			printf("minishell: %s: command not found\n", list->command);
			return (0);
		}
		if (ft_strnstr(list->command, "\\", ft_strlen(list->command)))
		{
			printf("minishell: %s: command not found\n", list->command);
			return (0);
		}
		if (execute_error_control(list) == 0)
			return (0);
		if (pids_funcion(list, status) == 0)
			return (0);
		return (0);
	}
	return (0);
}

int	execute_error_control(t_com *list)
{
	DIR	*dir;
	int	has_slash;

	has_slash = 0;
	if (ft_strchr(list->command, '/'))
		has_slash = 1;
	if (list->path_command == NULL)
	{
		if (!has_slash)
			return (list->vars->exit_status = 127, ft_printf(2, "minishell: %s: command not found\n", list->command), 0);
		if (access(list->command, F_OK) == -1)
			return (list->vars->exit_status = 127, ft_printf(2, "minishell: %s: No such file or directory\n", list->command), 0);
		dir = opendir(list->command);
		if (dir != NULL)
			return (list->vars->exit_status = 126, closedir(dir), ft_printf(2, "minishell: %s: Is a directory\n", list->command), 0);
		if (access(list->command, X_OK) == -1)
			return (list->vars->exit_status = 126, ft_printf(2, "minishell: %s: Permission denied\n", list->command), 0);
	}
	return (1);
}

int	pids_funcion(t_com *list, int status)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (write(2, "minishell: ", 11), perror("fork"), 0);
	if (pid == 0)
	{
		//setup_signals_default();
		apply_redirections(list);
		if (execve(list->path_command, list->command_arg, list->vars->env) == 0)
		{
			write(2, "minishell: ", 11);
			perror("execve");
			list->vars->exit_status = 127;
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	execute_signals(list, status);
	return (1);
}

void	execute_signals(t_com *list, int status)
{
	int	sig;

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
	else if (WIFEXITED(status))
		list->vars->exit_status = WEXITSTATUS(status);
}
