/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:57:33 by roo               #+#    #+#             */
/*   Updated: 2025/10/24 12:34:39 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void setup_pipeline(t_com *list)
{
	t_com *tmp_list;
	int pipe_fd[2];
	
	tmp_list = list;
	while (tmp_list && tmp_list->next) // Crear pipe entre comando actual y siguiente
	{
		if (pipe(pipe_fd) == -1) // Crea una conexión para comunicación entre procesos, es un canal unidireccional donde la salida de un proceso se convierte en la entrada de otro
			return(write(2, "minishell: ", 11), perror("pipe"));
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

void execute_pipeline(t_com *list)
{
    t_com *tmp_list;
	pid_t *pids;
    int status;
    int num_cmds;
	int i;
    
    tmp_list = list;
    num_cmds = 0;
	i = 0;
    while (tmp_list) // Contar comandos
    {
        num_cmds++;
        tmp_list = tmp_list->next;
    }
	    pids = malloc(sizeof(pid_t) * num_cmds); // Array para guardar PIDs
    execute_pipelines2(list, pids);
    tmp_list = list; // Cerrar TODOS los pipes en el padre
    while (tmp_list)
    {
        clean_fds(tmp_list);
        tmp_list = tmp_list->next;
    }
    while (i < num_cmds)
	{
    	waitpid(pids[i], &status, 0);
	    if (i == num_cmds - 1 && WIFEXITED(status)) // El exit status del último comando es el que importa
    	    list->vars->exit_status = WEXITSTATUS(status);
		i++;
	}
    free(pids);
}

void execute_pipelines2(t_com *list, pid_t *pids)
{
	t_com *tmp_list;
    pid_t pid;
	int i;
	
	i = 0;
    tmp_list = list;
    while (tmp_list) // Crear un proceso para cada comando
    {
		if(tmp_list->redirects->redirected != 1)
		{
			//tmp_list->redirects->redirected = 1;	
			set_redirections(tmp_list); // Configura redirecciones ANTES del fork
		}
        pid = fork();
        if (pid == -1)
            return(write(2, "minishell: ", 11), ("fork"), free(pids));
        if (pid == 0) // PROCESO HIJO
        {
            apply_redirections(tmp_list); // Aplica fd_in y fd_out
            close_pipes(list, tmp_list); // Cerrar TODOS los pipes que no usa este comando
            if (tmp_list->flag_built) // Ejecutar comando (built-in o externo)
            {
                commands_control(tmp_list, tmp_list->vars);
                exit(0); // ¡IMPORTANTE! Built-ins deben salir
            }
            else
            {
                tmp_list->path_command = get_path(tmp_list->command, tmp_list->vars->env, tmp_list);
                if (!tmp_list->path_command)
                {
                    ft_printf(2, "minishell: %s: command not found\n", tmp_list->command);
                    exit(127);
                }
                if (execve(tmp_list->path_command, tmp_list->command_arg, tmp_list->vars->env) == -1)
                {
					write(2, "minishell: ", 11), 
                    perror("execve");
                    exit(127);
                }
            }
        }
        pids[i++] = pid; // PROCESO PADRE
        tmp_list = tmp_list->next;
    }
}
void close_pipes(t_com *list, t_com *current_cmd)
{
    t_com *tmp_list;
    
    tmp_list = list;
    while (tmp_list)
    {
        if (tmp_list != current_cmd) // Cerrar pipes que NO son de este comando
        {
            if (tmp_list->fd_in != STDIN_FILENO)
                close(tmp_list->fd_in);
            if (tmp_list->fd_out != STDOUT_FILENO)
                close(tmp_list->fd_out);
        }
        tmp_list = tmp_list->next;
    }
}
