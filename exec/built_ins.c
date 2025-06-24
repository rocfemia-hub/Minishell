#include "minishell.h"

void	echo_function(t_com *vars)
{
	int		i;
	int		newline;
	ssize_t	bytes_written;

	i = 1;
	newline = 1;
	bytes_written = 0;
	if (vars->arg[i] && ft_strnstr(vars->arg, "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (vars->arg[i] && bytes_written != -42)
	{
		bytes_written = write(vars->fd_out, vars->arg, ft_strlen(vars->arg));
		if (vars->arg[i + 1])
			bytes_written = write(vars->fd_out, " ", 1);
		i++;
	}
	if (newline)
		write(vars->fd_out, "\n", 1);
}

void	pwd_function(t_com *vars)
{
	char	cwd[1024];
	ssize_t	bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) //getcwd me dice el directorio que estoy actualemte, es gestion de errores
		return (perror("pwd"));
	bytes_written = write(vars->fd_out, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(vars->fd_out, "\n", 1);
}
