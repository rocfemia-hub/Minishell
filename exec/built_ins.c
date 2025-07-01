#include "minishell.h"

void echo_function(t_com *list, t_vars *vars)
{
	int i;
	int newline;
	char **args;

	if (!list->arg || !*list->arg)
		return (void)write(vars->fd_out, "\n", 1);
	args = ft_split(list->arg, ' ');
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

void pwd_function(t_com *list, t_vars *vars)
{
	char cwd[1024];
	ssize_t bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) // getcwd me dice el directorio que estoy actualemte, es gestion de errores
		return (perror("pwd"));
	bytes_written = write(vars->fd_out, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(vars->fd_out, "\n", 1);
}

// FALTA COMPROBAR SI FUNCIONA CORRECTAMENTE
void	exit_function(t_com *list, t_vars *vars) // gestiona el exit de maera que salga por la salida de error que deba salir
{
	if (vars->argc == 1) // argc = 1: solo "exit"
        exit(0);
    if (vars->argc == 2) // argc = 2: "exit" + un argumento
    {
        if (valid_number(vars->argv[1])) // verifica si protege tu programa de numeros inválidos
            exit(ft_atoi(vars->argv[1]));
        else
        {
            write(2, "exit: numeric argument required\n", 32);
            exit(2);
        }
    }
    write(2, "exit: too many arguments\n", 25);
    exit(1);
}

// FALTA COMPROBAR SI FUNCIONA CORRECTAMENTE
void env_function(t_com *list, t_vars *vars) // gestiona la impresión de env
{
    int i = 0;
    
    if (!vars->env)
        return;
    while (vars->env[i])
    {
        write(vars->fd_out, vars->env[i], ft_strlen(vars->env[i])); // simplemente imprime linea a linea lo que hay en el env, sin opciones ni argmentos (lo pone en el subject)
        write(vars->fd_out, "\n", 1);
        i++;
    }
}

// FALTA COMPROBAR SI FUNCIONA CORRECTAMENTE
void cd_function(t_com *list, t_vars *vars)
{
    if (!list->arg || !*list->arg) // cd debe tener SOLO un argumento
        return(write(2, "cd: missing argument\n", 21));
    char **args = ft_split_mini(list->arg, ' '); // Separa argumentos para verificar que solo hay uno
    if (!args || !args[0])
        return(ft_free_free(args), write(2, "cd: missing argument\n", 21));
    if (args[1]) // Verifica que solo hay un argumento
        return(write(2, "cd: too many arguments\n", 23), ft_free_free(args));
    if (chdir(args[0]) == -1) // Intentar cambiar al directorio
    {
        write(2, "cd: ", 4);
        write(2, args[0], ft_strlen(args[0]));
        write(2, ": No such file or directory\n", 28);
        ft_free_free(args);
        return;
    }
    ft_free_free(args);
}
