#include "../minishell.h"

void commands_control(t_com *list, t_vars *vars) //añado ambas estructuras en todas lsa funciones por si acaso
{
	if (!list || !list->command)
		return;
	if (list->command && ft_strnstr(list->command, "echo", 4))
		echo_function(list, vars);
	if (list->command && ft_strnstr(list->command, "pwd", 3))
		pwd_function(list, vars);
	if (list->command && ft_strnstr(list->command, "exit", 4))
        exit_function(list, vars);
	if (list->command && ft_strnstr(list->command, "env", 3))
        env_function(list, vars);
}

void init_vars(t_vars *vars, int argc, char **argv,  char **env)
{
	vars->argc = argc;
	vars->argv = argv;
	vars->env = env;
	vars->fd_out = 1;
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

	if (!argc && argv)
		return 1;
	ft_bzero(&commands, sizeof(commands));
	ft_bzero(&vars, sizeof(vars)); //malloc d la nueva struct
	init_vars(&vars, argc, argv, env);
	while (1)
	{
		line = readline("minishell-> ");
		if (!line || !line_break(line))
			continue;
		commands = token(line); // llama a la funcion tokeniza
		// printf("%s\n", commands->command);
		if (commands && commands->command && ft_strnstr(commands->command, "error", 5))
		{
			printf("error\n");
			continue;
		}
		commands_control(commands, &vars); // llama a la funcion del de bultins
		free(line);
		free_list(commands);
	}
}
