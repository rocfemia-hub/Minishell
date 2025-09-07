/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:55 by roo               #+#    #+#             */
/*   Updated: 2025/09/07 19:49:13 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_vars(t_vars *vars, int argc, char **argv,  char **env)
{
	vars->argc = argc;
	vars->argv = argv;
	vars->env = env;
}

void init_fds(t_com *list, t_vars *vars)
{   
    while (list) // Valores por defecto
    {
        list->fd_in = STDIN_FILENO; // 0
        list->fd_out = STDOUT_FILENO; // 1
        list->vars = vars; // Asignar vars a todos
        if (list->next) // Si hay siguiente comando, necesitamos pipe
            list->flag_pipe = 1; // Se configurará en create_pipes()
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
	t_vars vars; //nueva struct

	if (argc < 1 && !argv)
		return 1;
	commands = NULL; // la verdad aqui no tengo del todo calro porque no se hace malloc
	//ft_bzero(&commands, sizeof(commands)); // usa calloc mjr (recomendacion de jainavas)
	ft_bzero(&vars, sizeof(vars)); //malloc d la nueva struct
	init_vars(&vars, argc, argv, env);
	while (1)
	{
		line = readline("minishell-> ");
		if (!line) // Ctrl+D
			break;
		if (line[0] == '\0')
			continue;
		add_history(line); // añade al historial para poder usar las flechitas arriba y abajo
		if (!line_break(line))
		{
			free(line);
			continue;
		}
		commands = token(line); // llama a la funcion tokeniza
		if (!commands) // debug para comprobar que el comando sea valido
        {
			(printf("Error: failed to parse command\n"), free(line));
            continue;
        }
		//commands->vars = &vars; // Estas tres inicializaciones son temporales, hay que hacerlo bien iniciando cada una nodo a nodo, porque ahora solo funcionan una sola vez.
		//commands->fd_out = 1; // TEMPORAL!!!!  hay que CAMBIAR esto, el 1 es para poder probar que funcione el ejecutor y los builtings
		//commands->fd_in = 0; // TEMPORAL!!!!  hay que CAMBIAR esto, el 0 es para poder probar que funcione el ejecutor y los builtings
		//commands = commands->next; //para que funcione con mas de un comando
		// printf("%s\n", commands->command);
		if (!commands->command) 
		{
			printf("Error: empty command\n");
    		(free(line), free_list(commands));
    		continue;
		}
		if (commands && commands->command && ft_strnstr(commands->command, "error", 5))
		{
			printf("error\n");
			(free(line), free_list(commands));
			continue;
		}
		(init_fds(commands, &vars), setup_pipeline(commands), execute_control(commands, &vars));
		free(line);
		//free_list(commands);
		commands = NULL; // reseteamos el puntero
	}
	return(0);
}
