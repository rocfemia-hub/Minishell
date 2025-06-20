#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	t_vars *vars;
	char *line;

	vars = ft_calloc(1, sizeof(t_vars));
	vars->output_fd = 1;
	if (!argc && argv)
		return 1;
	while (1)
	{
		line = readline("minishell-> ");
		if (!line)
			return (0);
		if (!token(line)) // llama a la funcion de parser
			break;
		// if (vars->params[0] && ft_strncmp(vars->params[0], "exit", 5) == 0)
		// 	break;
		// commands_control(vars); // llama a la funcion del de bultins
		// ft_free_free(vars->params);
		// free(line);
	}
}

void commands_control(t_vars *vars)
{
	if (vars->params[0] && ft_strncmp(vars->params[0], "echo", 5) == 0)
		echo_function(vars);
	if (vars->params[0] && ft_strncmp(vars->params[0], "pwd", 4) == 0)
		pwd_function(vars);
}
