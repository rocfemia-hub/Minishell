/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/02 14:19:26 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_signal; // variable global única

void init_env(t_vars *vars)
{
	char cwd[1024];
	char *pwd_str;

	vars->env = ft_calloc(5, sizeof(char *));
	if (!vars->env)
		return;
	getcwd(cwd, sizeof(cwd)); // getcwd me dice el directorio que estoy actualemte
	pwd_str = ft_strjoin("PWD=", cwd);
	vars->env[0] = pwd_str;
	vars->env[1] = ft_strdup("SHLVL=1");
	vars->env[2] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin");
	vars->env[3] = ft_strdup("_=/usr/bin/env");
	vars->env[4] = NULL;
}

void init_vars(t_vars *vars, int argc, char **argv, char **env)
{
	if(!env || !env[0])
		init_env(vars);
	else
		vars->env = env;
	vars->exit_status = 0;
	vars->pwd = getcwd(NULL, 0);
	env_to_list(vars, vars->env);
}

void init_fds(t_com *list, t_vars *vars)
{
	while (list) // Valores por defecto
	{
		list->fd_in = STDIN_FILENO;	  // 0
		list->fd_out = STDOUT_FILENO; // 1
		list->vars = vars;			  // Asignar vars a todos
		if (list->next)				  // Si hay siguiente comando, necesitamos pipe
			list->flag_pipe = 1;	  // Se configurará en create_pipes()
		list = list->next;
	}
}

int line_break(char *line)
{
	int i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (0);
	while (line && line[i] == 32)
		i++;
	if (!line[i])
		return (0);
	else
		return (1);
}

int main(int argc, char **argv, char **env)
{
	char *line;
	t_com *commands;
	t_vars vars; // nueva struct

	if (argc < 1 && !argv)
		return 1;
	commands = NULL;			   // la verdad aqui no tengo del todo calro porque no se hace malloc
	ft_bzero(&vars, sizeof(vars)); // malloc d la nueva struct
	init_vars(&vars, argc, argv, env);
	setup_signals_interactive();   // Configurar señales para modo interactivo
	while (1)
	{
		g_signal = 0; // Reset signal status
		line = readline("minishell-> ");
		if (!line) // Ctrl+D
		{
			rl_clear_history();		 // Liberar historial de readline
			free_t_vars_list(&vars); // Liberar env_list
			printf("exit\n");
			break;
		}
		if (g_signal == SIGINT) // Ctrl+C en el prompt
		{
			vars.exit_status = 130;
			g_signal = 0; // Reset para que no interfiera con el próximo comando
		}
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		add_history(line); // añade al historial para poder usar las flechitas arriba y abajo
		if (!line_break(line))
		{
			free(line);
			continue;
		}
		commands = token(line, &vars);
		if (!commands)				   // debug para comprobar que el comando sea valido
		{
			free(line);
			continue;
		}
		if (!commands->command)
		{
			if (!commands->redirects)
			{
				printf("Error: empty command\n");
				(free(line), free_t_com_list(commands));
				continue;

			}
		}
		init_fds(commands, &vars);
		setup_pipeline(commands);
		execute_control(commands, &vars);
		setup_signals_interactive(); // Restaurar señales interactivas
		
		// Check if a signal was received and update exit status
		if (g_signal == SIGINT)
			vars.exit_status = 130;
		free(line);
		free_t_com_list(commands);
		commands = NULL; // reseteamos el puntero
	}
	return (0);
}
