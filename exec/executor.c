/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/07/14 14:17:20 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// recibir estructura de comando y hacer execve en funcion del contenido de la estructura
int	execute(t_com *list)
{
	char **command; // resultado de split de command_arg xq execve recibe un (char **)
	int	fd[2];
	int	pid1;
	
	if (pipe(fd) == -1)
		return (ft_printf("Error de creación de pipe\n"), -1);
	command = ft_split_mini(list->command_arg, ' '); // se hace split porque execve recibe un char **
	list->path_command = get_path(list->command, list->vars->env, list);
	if (list->path_command == NULL)
		return (ft_printf("Command not found\n"));
	//dprintf(1, "--->%s<---", list->command);
	pid1 = fork();
	if (pid1 == 0)
	{
		//dup2(list->fd_in, STDIN_FILENO); // TEMPORAL, esto se usará cuando me redireccionen la entrada o salida
		//dup2(fd[WRITE_FD], STDOUT_FILENO);
		//close_all(fd, list); // TEMPORAL, esto se usará cuando haya pipes y tenga que estar cerrando fds todo el rato
		if (execve(list->path_command, command, list->vars->env) == -1)
			return (ft_printf("Error de ejecución\n"), -1); // hay que echar un ojo a las salidad de error
	}
	waitpid(pid1, NULL, 0);
	return (0);
	//printf(list->path_command);
}

void	close_all(int fd[2], t_com *cmd)
{
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	close(cmd->fd_in);
	close(cmd->fd_out);
}
