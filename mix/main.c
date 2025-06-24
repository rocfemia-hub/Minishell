#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
    t_com *commands;

	if (!argc && argv)
		return 1;
	ft_bzero(&commands, sizeof(commands));
	while (1)
	{
		line = readline("minishell-> ");
		if(!line || ft_strlen(line) == 0)
			continue;
		commands = token(line); // llama a la funcion tokeniza
		commands_control(commands); // llama a la funcion del de bultins
		free(line);
	}
}

void commands_control(t_com *vars)
{
	if (!vars || !vars->command)
		return;
	if (vars->command && ft_strnstr(vars->command, "echo", 5) == 0)
		echo_function(vars);
	if (vars->command && ft_strnstr(vars->command, "pwd", 4) == 0)
		pwd_function(vars);
}
