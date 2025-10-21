/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:55 by roo               #+#    #+#             */
/*   Updated: 2025/10/21 19:34:05 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_vars(t_vars *vars, int argc, char **argv, char **env)
{
	vars->env = env;
	vars->exit_status = 0;
	env_to_list(vars, env);
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
	signal(SIGINT, handle_c);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN); // SIGQUITE control 4, SIG_ING es que ingnore
		line = readline("minishell-> ");
		if (!line) // Ctrl+D
		{
			rl_clear_history();		 // Liberar historial de readline
			free_t_vars_list(&vars); // Liberar env_list
			break;
		}
		if (line[0] == '\0')
			continue;
		add_history(line); // añade al historial para poder usar las flechitas arriba y abajo
		if (!line_break(line))
		{
			free(line);
			continue;
		}
		commands = token(line, &vars); // llama a la funcion tokeniza
		if (!commands)				   // debug para comprobar que el comando sea valido
		{
			free(line);
			continue;
		}
		if (!commands->command)
		{
			printf("Error: empty command\n");
			(free(line), free_t_com_list(commands));
			continue;
		}
		init_fds(commands, &vars);
		setup_pipeline(commands);
		execute_control(commands, &vars);
		free(line);
		free_t_com_list(commands);
		commands = NULL; // reseteamos el puntero
	}
	return (0);
}
