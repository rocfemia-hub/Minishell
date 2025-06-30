#include "../minishell.h"

void commands_control(t_com *vars)
{
	if (!vars || !vars->command)
		return;
	if (vars->command && ft_strnstr(vars->command, "echo", 4))
		echo_function(vars);
	if (vars->command && ft_strnstr(vars->command, "pwd", 3))
		pwd_function(vars);
	if (vars->command && ft_strnstr(vars->command, "exit", 4))
        exit_function(vars);
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

	if (!argc && argv)
		return 1;
	ft_bzero(&commands, sizeof(commands));
	commands->argc = argc; // Guarda valor de argc y argv en la estructura
	commands->argv = argv;
	while (1)
	{
		line = readline("minishell-> ");
		if (!line || !line_break(line))
			continue;
		commands = token(line);		// llama a la funcion tokeniza
		// printf("%s\n", commands->command);
		if (commands->command && ft_strnstr(commands->command, "error", 5))
		{
			printf("error\n");
			continue;
		}
		commands_control(commands); // llama a la funcion del de bultins
		free(line);
		free_list(commands);
	}
}
