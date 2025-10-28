/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/10/27 21:00:20 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redirections_control(t_com *list, int j, int q, int k)
{
	int i;

	i = -1;
	if (list->redirects == NULL)
		return(0);
	if (list->redirects->redirect_heredoc) // Heredoc toma prioridad sobre otras redirecciones de input
    	return(heredoc_execution(list), list->redirects->redirected = 1, 1);
	if (list->redirects->type_redirec) // sino peta el programa cuando no hay redirecciones
	{
		while (list->redirects->type_redirec[++i] != 0) // cambio el ++ porque sino no miro el primer digito 
		{
			if (list->redirects->type_redirec[i] == 1) 
				if(!infile_redirection(list, j++))
					return (0);
			if (list->redirects->type_redirec[i] == 2) 
				if(!outfile_redirection(list, q++))
					return (0);
			if (list->redirects->type_redirec[i] == 3) 
				if(!append_redirection(list, k++))
					return (0);
		}
	}
	return(1);
}

int infile_redirection(t_com *list, int i)
{
	int tmp_fd;

	if (list->redirects->redirect_in && list->redirects->input_file)
	{
		tmp_fd = open(list->redirects->input_file[i], O_RDONLY);
		if (tmp_fd == -1)
			return(write(2, "minishell: ", 11), perror(list->redirects->input_file[i]), 0);
		if (list->fd_in != 0)
            close(list->fd_in);
        list->fd_in = tmp_fd;
	}
	return(1);
}

int outfile_redirection(t_com *list, int i)
{
	int tmp_fd;

    if (list->redirects->output_file && list->redirects->output_file[i])
    {
        tmp_fd = open(list->redirects->output_file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (tmp_fd == -1)
            return(write(2, "minishell: ", 11), perror(list->redirects->output_file[i]), 0); //AQUIIIIIIIIIIIII echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
        if (list->fd_out != 1)
            close(list->fd_out);
        list->fd_out = tmp_fd;
    }
	return(1);
}

int	append_redirection(t_com *list, int i)
{
    int tmp_fd;

    if (list->redirects->append_file && list->redirects->append_file[i])
    {
        tmp_fd = open(list->redirects->append_file[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (tmp_fd == -1)
            return(write(2, "minishell: ", 11), perror(list->redirects->append_file[i]), 0);
        if (list->fd_out != 1)
            close(list->fd_out);
        list->fd_out = tmp_fd;
    }
	return(1);
}

void heredoc_execution(t_com *list)
{
	char *line;
	char *temp_file;
	int fd;
	char *num_str;
	static int heredoc_count = 0;
	
	num_str = ft_itoa(heredoc_count++); // Crear nombre único para archivo temporal
	temp_file = ft_strjoin("/tmp/.heredoc_", num_str);
	free(num_str);
	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600); // Crear archivo temporal
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror("heredoc");
		free(temp_file);
		return;
	}
	while (1) // Leer líneas hasta encontrar delimiter
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(list->redirects->delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		if (ft_strncmp(line, list->redirects->delimiter, ft_strlen(list->redirects->delimiter) + 1) == 0) // Comparar con delimiter
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line)); // Escribir al archivo temporal
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	list->redirects->heredoc_file = temp_file;
	list->fd_in = open(temp_file, O_RDONLY, 0777);
}

void apply_redirections(t_com *list)
{
	if (list->fd_in != STDIN_FILENO) // Aplicar redirección de entrada
	{
		if (dup2(list->fd_in, STDIN_FILENO) == -1)
		{
			write(2, "minishell: ", 11), 
			perror("dup2 stdin");
			exit(1);
		}
		close(list->fd_in);
		list->fd_in = 0;
	}
	if (list->fd_out != STDOUT_FILENO) // Aplicar redirección de SALIDA
	{
		if (dup2(list->fd_out, STDOUT_FILENO) == -1)
		{
			write(2, "minishell: ", 11), 
			perror("dup2 stdout");
			exit(1);
		}
		close(list->fd_out);
		list->fd_out = 1;
	}
}

void clean_fds(t_com *list)
{
    if (list->fd_in != STDIN_FILENO)
        close(list->fd_in);
    if (list->fd_out != STDOUT_FILENO)
        close(list->fd_out);
	list->fd_in = STDIN_FILENO;
	list->fd_out = STDOUT_FILENO;
	if (list->redirects && list->redirects->heredoc_file)
    {
        unlink(list->redirects->heredoc_file); // Borrar archivo
        free(list->redirects->heredoc_file);
        list->redirects->heredoc_file = NULL;
    }
}
