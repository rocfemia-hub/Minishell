/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:33 by roo               #+#    #+#             */
/*   Updated: 2025/07/24 01:30:43 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_function(t_com *list, t_vars *vars)
{ // Ya funciona correctamente :)))
	int i;
	int newline;

	if (!list->args || !*list->args)
		return (void)write(list->fd_out, "\n", 1);
	i = 0;
	newline = 1;
	while (list->args[i] && valid_n_option(list->args[i]))
	{
		newline = 0;
		i++;
	}
	while (list->args[i])
	{
		write(list->fd_out, list->args[i], ft_strlen(list->args[i]));
		if (list->args[i + 1])
			write(list->fd_out, " ", 1);
		i++;
	}
	if (newline)
		write(list->fd_out, "\n", 1);
}

void pwd_function(t_com *list, t_vars *vars)
{ // Ya funciona correctamente :)))
	char cwd[1024];
	ssize_t bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) // getcwd me dice el directorio que estoy actualemte, es gestion de errores
		return (perror("pwd"));
	bytes_written = write(list->fd_out, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(list->fd_out, "\n", 1);
}

void exit_function(t_com *list, t_vars *vars)
{  // Ya funciona correctamente :)))
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

void cd_function(t_com *list, t_vars *vars)
{ // Ya funciona correctamente :)))
	if (!list->args || !*list->args) // cd debe tener SOLO un argumento
	{
		write(2, "cd: missing argument\n", 21);
		return;
	}
	if (!list->args  || !list->args [0])
	{
		ft_free_free(list->args );
		list->args = NULL;
		write(2, "cd: missing argument\n", 21);
		return ;
	}
	if (list->args [1]) // Verifica que solo hay un argumento
		return (write(2, "cd: too many arguments\n", 23), ft_free_free(list->args ));
	if (chdir(list->args [0]) == -1) // chdir cambia el directorio actual desde donde se ha ejecutado tu programa y pude recibir una ruta absoluta o relativa
	{
		write(2, "cd: ", 4);
		write(2, list->args [0], ft_strlen(list->args [0]));
		write(2, ": No such file or directory\n", 28);
		ft_free_free(list->args);
		list->args = NULL;
		return;
	}
}
