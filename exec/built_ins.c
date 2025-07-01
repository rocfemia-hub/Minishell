#include "minishell.h"

void echo_function(t_com *commands)
{
	int i;
	int newline;
	char **args;

	if (!commands->arg || !*commands->arg)
		return (void)write(commands->vars->fd_out, "\n", 1);
	args = ft_split(commands->arg, ' ');
	i = 0;
	newline = 1;
	while (args[i] && valid_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(commands->vars->fd_out, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(commands->vars->fd_out, " ", 1);
		i++;
	}
	if (newline)
		write(commands->vars->fd_out, "\n", 1);
	ft_free_free(args);
}

void pwd_function(t_com *commands)
{
	char cwd[1024];
	ssize_t bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) // getcwd me dice el directorio que estoy actualemte, es gestion de errores
		return (perror("pwd"));
	bytes_written = write(commands->vars->fd_out, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(commands->vars->fd_out, "\n", 1);
}

void	exit_function(t_com *commands) // gestiona el exit de maera que salga por la salida de error que deba salir
{
	if (commands->vars->argc == 1) // argc = 1: solo "exit"
        exit(0);
    if (commands->vars->argc == 2) // argc = 2: "exit" + un argumento
    {
        if (valid_number(commands->vars->argv[1])) // verifica si protege tu programa de numeros inválidos
            exit(ft_atoi(commands->vars->argv[1]));
        else
        {
            write(2, "exit: numeric argument required\n", 32);
            exit(2);
        }
    }
    write(2, "exit: too many arguments\n", 25);
    exit(1);
}