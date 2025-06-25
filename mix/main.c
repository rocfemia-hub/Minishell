#include "../minishell.h"

void commands_control(t_com *vars)
{
	if (!vars || !vars->command)
		return;
	if (vars->command && ft_strnstr(vars->command, "echo", 4))
		echo_function(vars);
	if (vars->command && ft_strnstr(vars->command, "pwd", 3))
		pwd_function(vars);
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
	while (1)
	{
		line = readline("minishell-> ");
		if (!line || !line_break(line))
			continue;
		commands = token(line);		// llama a la funcion tokeniza
		commands_control(commands); // llama a la funcion del de bultins
		free(line);
	}
}
