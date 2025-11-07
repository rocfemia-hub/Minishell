/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/07 14:53:49 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char *cmd, t_vars *vars)
{
	int		i;
	t_env	*node;
	char	**paths;
	char	*result;

	if ((!cmd) || access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	node = find_env_var(vars, "PATH");
	if (!node)
		return (NULL);
	paths = ft_split(node->env_inf, ':');
	i = -1;
	while (paths[++i])
	{
		result = ft_strjoin(paths[i], "/");
		result = ft_strjoin_gnl(result, cmd);
		if (access(result, X_OK) == 0)
			break ;
		free(result);
		result = NULL;
	}
	return (ft_free_free(paths), result);
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
			return (ft_printf(2, "minishell: %s: command not found\n",
					list->command), list->vars->exit_status = 127, 0);
		if (access(list->command, F_OK) == -1)
			return (ft_printf(2, "minishell: %s: No such file or directory\n",
					list->command), list->vars->exit_status = 127, 0);
		dir = opendir(list->command);
		if (dir != NULL)
			return (ft_printf(2, "minishell: %s: Is a directory\n",
					list->command), list->vars->exit_status = 126,
				closedir(dir), 0);
		if (access(list->command, X_OK) == -1)
			return (ft_printf(2, "minishell: %s: Permission denied\n",
					list->command), list->vars->exit_status = 126, 0);
	}
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
