/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/10/15 16:29:02 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_control(t_com *list, t_vars *vars)
{
	t_com *tmp_list;

	signal(SIGQUIT, handle_backslash);
	tmp_list = list;
	if (tmp_list->next == NULL) // si solo hay un comando
	{
		if (!set_redirections(tmp_list)) // Si falla, no ejecutar
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
	else // mas de un comando (con pipes)
	{
		setup_pipeline(list);
		execute_pipeline(list); // Nueva función
	}
}

void commands_control(t_com *list, t_vars *vars)
{ // printf("list->command = '%s' \n", list->command); //dprintf(1, "--->%s<---\n", list->command); //dprintf(1, "--->%s<---\n", list->command_arg); //dprintf(1, "--->%s<---\n", list->args[1]);
	if (!list || !list->command)
		return;
	if (!set_redirections(list))
		return;
	if (list->flag_built == 1)
	{
		if (list->command && ft_strnstr(list->command, "echo", 5)) // 5 para incluir '\0'
			echo_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "pwd", 4)) // 4 para incluir '\0'
			pwd_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "exit", 5)) // 5 para incluir '\0' PONER BYE
			exit_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "env", 4)) // 4 para incluir '\0'
			env_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "cd", 3)) // 3 para incluir '\0'
			cd_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "export", 7)) // 7 para incluir '\0'
			export_function(list, vars);
		else if (list->command && ft_strnstr(list->command, "unset", 6)) // 6 para incluir '\0'
			unset_function(list, vars);
		clean_fds(list);
	}
	else
		execute(list, vars);
}

char *get_path(char *cmd, char **envp, t_com *pipex)
{
	char **paths;
	char *result;

	if ((!cmd) || access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	pipex->i = -1;
	while (envp[++pipex->i])
		if (ft_strncmp(envp[pipex->i], "PATH=", 5) == 0)
			break;
	if (envp[pipex->i] == NULL)
		return (NULL);
	paths = ft_split(&envp[pipex->i][5], ':');
	pipex->i = -1;
	while (paths[++pipex->i])
	{
		result = ft_strjoin(paths[pipex->i], "/");
		result = ft_strjoin_gnl(result, cmd);
		if (access(result, X_OK) == 0)
			break;
		free(result);
		result = NULL;
	}
	if (result == NULL)
		return (result);
	return (ft_free_free(paths), result);
}

int execute(t_com *list, t_vars *vars)
{ // recibir estructura de comando y hacer execve en funcion del contenido de la estructura
	int pid;
	int status;
	DIR *dir;	   // esto es necesario para opendir, esa función devuele un dir *, esto es una variable que representa un directorio abrierto, como un puntero hacia el
	int has_slash; // para saber si es ruta especifica o no

	list->path_command = get_path(list->command, list->vars->env, list);
	if (ft_strnstr(list->command, ";", ft_strlen(list->command)) || ft_strnstr(list->command, "\\", ft_strlen(list->command)))
		return (printf("minishell: %s: command not found\n", list->command), 0);
	has_slash = ft_strchr(list->command, '/') != NULL;
	if (list->path_command == NULL)
	{
		if (!has_slash) // Si tiene '/', se trata como ruta explícita
		{
			list->vars->exit_status = 127;
			return (printf("minishell: %s: command not found\n", list->command), 0);
		}
		if (access(list->command, F_OK) == -1)
		{
			list->vars->exit_status = 1;
			return (printf("minishell: %s: No such file or directory\n", list->command), 0);
		}
		dir = opendir(list->command);
		if (dir != NULL)
		{
			list->vars->exit_status = 126;
			return (closedir(dir), printf("minishell: %s: Is a directory\n", list->command), 0);
		}
		if (access(list->command, X_OK) == -1)
		{
			list->vars->exit_status = 126;
			return (printf("minishell: %s: Permission denied\n", list->command), 0);
		}
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 0);
	if (pid == 0)
	{
		apply_redirections(list);
		if (execve(list->path_command, list->command_arg, list->vars->env) == 0) // CUIDADO CON ENV
		{
			perror("execve");
			list->vars->exit_status = 127;
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		list->vars->exit_status = WEXITSTATUS(status); // investigar bienn que es el WEXITSTATUS
	ft_free_free(list->command_arg);
	if (list->path_command)
		free(list->path_command);
	return (0); // dprintf(1, "--->%s<---", list->command);
}
