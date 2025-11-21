/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/12 00:03:03 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_directory(const char *path)
{
	DIR	*dir;

	if (!path || !*path || ft_strncmp(path, ".", 2) == 0
		|| ft_strncmp(path, "..", 2) == 0)
		return (0);
	if (access(path, F_OK) == -1)
		return (0);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

char	*get_path(char *cmd, t_vars *vars)
{
	char	*result;
	char	**paths;
	int		i;
	t_env	*node;

	if (!cmd || !*cmd || ft_strncmp(cmd, ".", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "..", ft_strlen(cmd)) == 0)
		return (NULL);
	if (access(cmd, X_OK) == 0 && !is_directory(cmd))
		return (ft_strdup(cmd));
	node = find_env_var(vars, "PATH");
	if (!node)
		return (NULL);
	i = -1;
	paths = ft_split(node->env_inf, ':');
	while (paths && paths[++i])
	{
		result = ft_strjoin(paths[i], "/");
		result = ft_strjoin_gnl(result, cmd);
		if (access(result, X_OK) == 0 && !is_directory(result))
			break ;
		free(result);
		result = NULL;
	}
	return (ft_free_free(paths), result);
}

static int	execute_error_control(t_com *list)
{
	char	*cmd;
	char	*path;

	cmd = list->command;
	if (!cmd || !*cmd || is_variable_assignment(cmd))
		return (1);
	path = cmd;
	if (list->path_command)
		path = list->path_command;
	if (ft_strchr(cmd, ';') || ft_strchr(cmd, '\\'))
		return (ft_printf(2, "minishell: %s: command not found\n", cmd),
			list->vars->exit_status = 127, 0);
	if (!list->path_command && !ft_strchr(cmd, '/'))
		return (ft_printf(2, "minishell: %s: command not found\n", cmd),
			list->vars->exit_status = 127, 0);
	if (access(path, F_OK) == -1)
		return (ft_printf(2, "minishell: %s: No such file or directory\n", cmd),
			list->vars->exit_status = 127, 0);
	if (is_directory(path))
		return (ft_printf(2, "minishell: %s: Is a directory\n", cmd),
			list->vars->exit_status = 126, 0);
	if (access(path, X_OK) == -1)
		return (ft_printf(2, "minishell: %s: Permission denied\n", cmd),
			list->vars->exit_status = 126, 0);
	return (1);
}

int	execute(t_com *list, t_vars *vars)
{
	int	status;

	status = 0;
	list->path_command = get_path(list->command, list->vars);
	if (list->command && vars)
	{
		if (ft_strnstr(list->command, ";", ft_strlen(list->command)))
			return (ft_printf(2, "minishell: %s: command not found\n",
					list->command), list->vars->exit_status = 127, 0);
		if (ft_strnstr(list->command, "\\", ft_strlen(list->command)))
			return (ft_printf(2, "minishell: %s: command not found\n",
					list->command), list->vars->exit_status = 127, 0);
		if (execute_error_control(list) == 0)
			return (0);
		if (pids_funcion(list, status) == 0)
			return (0);
		return (0);
	}
	return (0);
}

void	execute_signals(t_com *list, int status)
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
	else if (WIFEXITED(status))
		list->vars->exit_status = WEXITSTATUS(status);
}
