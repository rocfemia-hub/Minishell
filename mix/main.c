#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
    t_com *commands;

	if (!argc && argv)
		return 1;
	while (1)
	{
		line = readline("minishell-> ");
		if (!line)
			return (0);
		commands = token(line); // llama a la funcion tokeniza
		commands_control(commands); // llama a la funcion del de bultins
		// ft_free_free(vars->params);
		// free(line);
	}
}

void commands_control(t_com *vars)
{
	if (vars->command && ft_strncmp(vars->command, "echo", 5) == 0)
		echo_function(vars);
	if (vars->command && ft_strncmp(vars->command, "pwd", 4) == 0)
		pwd_function(vars);
}
