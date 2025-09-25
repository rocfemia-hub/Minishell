/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 16:52:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_control(t_com *list, t_vars *vars)
{
	set_redirections(list);
	if(list->next == NULL)
		commands_control(list, vars); // llama a la funcion del de bultins
	// si llega aquí significa que hay más de un comando y habría que crear una pipe
	// dentro de la pipe hay que ir comprobando continuamente si es builting o no
	clean_fds(list);
}

void setup_pipeline(t_com *list)
{
	t_com *tmp_list = list;
    int pipe_fd[2];
    
    while (tmp_list && tmp_list->next) // Crear pipe entre comando actual y siguiente
    {
        if (pipe(pipe_fd) == -1) // Crea una conexión para comunicación entre procesos, es un canal unidireccional donde la salida de un proceso se convierte en la entrada de otro
            return(perror("pipe"));
        tmp_list->fd_out = pipe_fd[WRITE_FD]; // El comando actual escribirá al pipe
        tmp_list->next->fd_in = pipe_fd[READ_FD]; // El siguiente comando leerá del pipe
        set_redirections(tmp_list); // Configurar redirecciones individuales (pueden sobrescribir pipes)
        tmp_list = tmp_list->next;
    }
    if (tmp_list) // Último comando, configura sus redirecciones
        set_redirections(tmp_list);
}

void commands_control(t_com *list, t_vars *vars)
{ //printf("list->command = '%s' \n", list->command); //dprintf(1, "--->%s<---\n", list->command); //dprintf(1, "--->%s<---\n", list->command_arg); //dprintf(1, "--->%s<---\n", list->args[1]);
	if(list->flag_built == 1)
	{
		if (!list || !list->command)
			return;
		else if (list->command && ft_strnstr(list->command, "echo", 5)) // 5 para incluir '\0'
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
		return (ft_printf("Command not found\n"), -1);
	pid1 = fork();
	if (pid1 == 0)
	{
		execute_two(list, fd);
		if (execve(list->path_command, list->command_arg, list->vars->env) == -1)
			return (ft_printf("Error de ejecución\n"), -1); // hay que echar un ojo a las salidad de error
	}
	close(fd[READ_FD]);
    close(fd[WRITE_FD]);
	waitpid(pid1, NULL, 0);
	ft_free_free(list->command_arg);
	if (list->path_command)
		free(list->path_command);
	return (0); //dprintf(1, "--->%s<---", list->command);
}

void execute_two(t_com *list, int fd[2])
{
	if (list->fd_in != STDIN_FILENO) // 0
		{
			if(dup2(list->fd_in, STDIN_FILENO) == -1) // Esto se usará cuando me redireccionen la entrada o salida
				perror("dup2 stdin");
			close(list->fd_in);
		}
		if (list->fd_out != STDOUT_FILENO) // 1
		{
			if(dup2(list->fd_out, STDOUT_FILENO) == -1)
				perror("dup2 stdout");
			close(list->fd_out);
		}
	close(fd[READ_FD]);
    close(fd[WRITE_FD]);
}
