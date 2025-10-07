/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/10/06 18:43:21 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_control(t_com *list, t_vars *vars)
{
	signal(SIGQUIT, handle_backslash);
	set_redirections(list);
	if(list->next == NULL) // un solo comando
		commands_control(list, vars); // llama a la funcion del de bultins
	else
	{
		// si llega aquí significa que hay más de un comando y habría que crear una pipe
		// dentro de la pipe hay que ir comprobando continuamente si es builting o no
		commands_control(list, vars);	
	}
	clean_fds(list);
}

void commands_control(t_com *list, t_vars *vars)
{ //printf("list->command = '%s' \n", list->command); //dprintf(1, "--->%s<---\n", list->command); //dprintf(1, "--->%s<---\n", list->command_arg); //dprintf(1, "--->%s<---\n", list->args[1]);
	if (!list || !list->command)
		return;
	if(list->flag_built == 1)
	{
		set_redirections(list);
		if (list->command && ft_strnstr(list->command, "echo", 5)) // 5 para incluir '\0'
			echo_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "pwd", 4)) // 4 para incluir '\0'
			pwd_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "exit", 5)) // 5 para incluir '\0'
			exit_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "env", 4)) // 4 para incluir '\0'
			env_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "cd", 3)) // 3 para incluir '\0'
			cd_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "export", 7)) // 7 para incluir '\0'
			export_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "unset", 6)) // 6 para incluir '\0'
			unset_function(list, vars);
		else
			printf("Command '%s' not found\n", list->command); // no se si hace algo ahora mismo o se puede borrar
		clean_fds(list);
	}
	else
		execute(list);
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

int	execute(t_com *list)
{ // recibir estructura de comando y hacer execve en funcion del contenido de la estructura
	int	fd[2];
	int	pid1;
	
	if (pipe(fd) == -1)
		return (ft_printf("Error de creación de pipe\n"), -1);
	list->path_command = get_path(list->command, list->vars->env, list);
	if (list->path_command == NULL)
		return (ft_printf("minishell: %s: command not found\n", list->command), -1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"), -1);
	if (pid1 == 0)
	{
		set_redirections(list);
		apply_redirections(list);
		if (execve(list->path_command, list->command_arg, list->vars->env) == -1) // CUIDADO CON ENV
		{
			perror("execve");
			exit(127);
		}
	}
	waitpid(pid1, NULL, 0);
	/*if (WIFEXITED(status))
		list->vars->exit_status = WEXITSTATUS(status);*/
	ft_free_free(list->command_arg);
	if (list->path_command)
		free(list->path_command);
	return (0); //dprintf(1, "--->%s<---", list->command);
}

void setup_pipeline(t_com *list)
{
	t_com *tmp_list;
	int pipe_fd[2];
	
	tmp_list = list;
	while (tmp_list && tmp_list->next) // Crear pipe entre comando actual y siguiente
	{
		if (pipe(pipe_fd) == -1) // Crea una conexión para comunicación entre procesos, es un canal unidireccional donde la salida de un proceso se convierte en la entrada de otro
			return(perror("pipe"));
		if (tmp_list->fd_out == STDOUT_FILENO)
			tmp_list->fd_out = pipe_fd[WRITE_FD];
		else
			close(pipe_fd[WRITE_FD]); // No necesitamos el pipe de salida
		if (tmp_list->next->fd_in == STDIN_FILENO)
			tmp_list->next->fd_in = pipe_fd[READ_FD];
		else
			close(pipe_fd[READ_FD]); // No necesitamos el pipe de entrada
		tmp_list = tmp_list->next;
	}
}
