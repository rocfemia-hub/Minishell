#include "minishell.h"

void echo_function(t_com *vars)
{
	int i;
	int newline;
	char **args;

	if (!vars->arg || !*vars->arg)
		return (void)write(vars->fd_out, "\n", 1);
	args = ft_split(vars->arg, ' ');
	i = 0;
	newline = 1;
	while (args[i] && valid_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(vars->fd_out, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(vars->fd_out, " ", 1);
		i++;
	}
	if (newline)
		write(vars->fd_out, "\n", 1);
	ft_free_free(args);
}

void pwd_function(t_com *vars)
{
	char cwd[1024];
	ssize_t bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) // getcwd me dice el directorio que estoy actualemte, es gestion de errores
		return (perror("pwd"));
	bytes_written = write(vars->fd_out, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(vars->fd_out, "\n", 1);
}
