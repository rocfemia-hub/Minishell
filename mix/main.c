#include "../minishell.h"

void commands_control(t_com *list, t_vars *vars)
{
	//printf("list->command = '%s' \n", list->command);
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

void init_vars(t_vars *vars, int argc, char **argv,  char **env)
{
	vars->argc = argc;
	vars->argv = argv;
	vars->env = env;
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
	commands = NULL; // la verdad aqui no tengo del todo calro porque no se hace malloc, pero claude dice que es así y yo le creo xd
	//ft_bzero(&commands, sizeof(commands)); // usa calloc mjr (recomendacion de jainavas)
	//ft_bzero(&vars, sizeof(vars)); //malloc d la nueva struct
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
			printf("Error: failed to parse command\n");
            free(line);
            continue;
        }
		commands->vars = &vars; // Estas tres inicializaciones son temporales, hay que hacerlo bien iniciando cada una nodo a nodo, porque ahora solo funcionan una sola vez.
		commands->fd_out = 1; // TEMPORAL!!!!  hay que CAMBIAR esto, el 1 es para poder probar que funcione el ejecutor y los builtings
		commands->fd_in = 0; // TEMPORAL!!!!  hay que CAMBIAR esto, el 0 es para poder probar que funcione el ejecutor y los builtings
		// printf("%s\n", commands->command);
		if (!commands->command) 
		{
    		printf("Error: empty command\n");
    		free(line);
    		free_list(commands);
    		continue;
		}
		if (commands && commands->command && ft_strnstr(commands->command, "error", 5))
		{
			printf("error\n");
			free(line);
            free_list(commands);
			continue;
		}
		commands_control(commands, &vars); // llama a la funcion del de bultins
		free(line);
		free_list(commands);
		commands = NULL; // reseteamos el puntero
	}
	return(0);
}
