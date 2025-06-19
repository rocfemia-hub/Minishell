#include "minishell.h"

void	echo_function(t_vars *vars)
{
	int		i;
	int		newline;
	ssize_t	bytes_written;

	i = 1;
	newline = 1;
	bytes_written = 0;
	if (vars->params[i] && ft_strncmp(vars->params[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (vars->params[i] && bytes_written != -42)
	{
		bytes_written = write(vars->output_fd, vars->params[i], ft_strlen(vars->params[i]));
		if (vars->params[i + 1])
			bytes_written = write(vars->output_fd, " ", 1);
		i++;
	}
	if (newline)
		write(vars->output_fd, "\n", 1);
}

void	pwd_function(t_vars *vars)
{
	char	cwd[1024];
	ssize_t	bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) //getcwd me dice el directorio que estoy actualemte, es gestion de errores
		return (perror("pwd"));
	bytes_written = write(vars->output_fd, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(vars->output_fd, "\n", 1);
}
