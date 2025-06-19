/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:57:17 by roo               #+#    #+#             */
/*   Updated: 2025/06/13 17:05:54 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_function(t_vars *vars)
{
	int		i;
	int		newline;
	ssize_t	bytes_written;

	i = 1;
	newline = 1;
	bytes_written = 0;

	//imprementacion del echo -n
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
	//imprementacion del echo -n
	if (newline)
		write(vars->output_fd, "\n", 1);
}

void	pwd_function(t_vars *vars)
{
	char	cwd[1024];
	ssize_t	bytes_written;

	if (getcwd(cwd, sizeof(cwd)) == NULL) //getcwd me dice el directorio que estoy actualemte, es gestion de errores
	{
		perror("pwd");
		return ;
	}
	bytes_written = write(vars->output_fd, cwd, ft_strlen(cwd));
	if (bytes_written != -1)
		write(vars->output_fd, "\n", 1);
}

// void	ls_function(t_vars *vars)
// {
// 	DIR				*dir; //variable de una estructura que me dice el directorio abierto
// 	struct dirent	*entry;

// 	dir = opendir("."); //abre el directorio y me dice en donde estoy
// 	if (!dir)
// 	{
// 		perror("ls");
// 		return ;
// 	}
// 	entry = readdir(dir); //lee la siguiente entrada del directorio (lo siguiente que hay)
// 	while (entry)
// 	{
// 		write(vars->output_fd, entry->d_name, strlen(entry->d_name));
// 		write(vars->output_fd, " ", 1);
// 		entry = readdir(dir);
// 	}
// 	write(vars->output_fd, "\n", 1);
// 	closedir(dir); //cierra del directorio
// }

