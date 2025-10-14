/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:32:04 by roo               #+#    #+#             */
/*   Updated: 2025/10/14 17:33:57 by roo              ###   ########.fr       */
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
		if (!set_redirections(tmp_list))  // Si falla, no ejecutar
    	    return(clean_fds(tmp_list));
        if (tmp_list->flag_built == 1)
            commands_control(tmp_list, vars);
        else
            execute(tmp_list);
        clean_fds(tmp_list);
    }
    else // mas de un comando (con pipes)
    {
        setup_pipeline(list);
        execute_pipeline(list); // Nueva función
    }
}

void commands_control(t_com *list, t_vars *vars)
{ //printf("list->command = '%s' \n", list->command); //dprintf(1, "--->%s<---\n", list->command); //dprintf(1, "--->%s<---\n", list->command_arg); //dprintf(1, "--->%s<---\n", list->args[1]);
	if (!list || !list->command)
		return;
	if(!set_redirections(list))
		return;
	if(list->flag_built == 1)
	{
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
	int pid;
    int status;
	DIR *dir; // esto es necesario para opendir, esa función devuele un dir *, esto es una variable que representa un directorio abrierto, como un puntero hacia el
	
	list->path_command = get_path(list->command, list->vars->env, list);
	if (list->path_command == NULL)
	{
		if (access(list->command, F_OK) == -1) // Verificar si existe
		{
			if (access(list->command, X_OK) == -1) // Verificar si tiene permisos de ejecución
            	return (printf("minishell: %s: Permission denied\n", list->command), 0);
			dir = opendir(list->command);
			if (dir != NULL)
            	return (closedir(dir), printf("minishell: %s: Is a directory\n", list->command), 0);
		}
		return (printf("minishell: %s: command not found\n", list->command), 0);
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
			exit(127);
		}
	}
	waitpid(pid, NULL, 0);
	if (WIFEXITED(status))
		list->vars->exit_status = WEXITSTATUS(status); // investigar bienn que es el WEXITSTATUS
	ft_free_free(list->command_arg);
	if (list->path_command)
		free(list->path_command);
	return (0); //dprintf(1, "--->%s<---", list->command);
}
