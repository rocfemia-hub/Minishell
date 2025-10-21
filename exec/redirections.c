/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/10/21 20:06:26 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int set_redirections(t_com *list)
{
	int i;
    int tmp_fd;
	
    if (list->redirects->output_file) // abrir archivos de output (aunque no escribas en ellos)
    {
        i = 0;
        while (list->redirects->output_file[i])
        {
            tmp_fd = open(list->redirects->output_file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (tmp_fd == -1)
                return(write(2, "minishell: ", 11), perror(list->redirects->output_file[i]), 0);
            if (list->redirects->output_file[i + 1] != NULL) // Si NO es el último, cierra
                close(tmp_fd);
            else
                list->fd_out = tmp_fd; // Solo el último se usa para escribir
            i++;
        }
    }
    if (list->redirects->append_file)
    {
        i = 0;
        while (list->redirects->append_file[i])
        {
            tmp_fd = open(list->redirects->append_file[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (tmp_fd == -1)
                return(write(2, "minishell: ", 11), perror(list->redirects->append_file[i]), 0);
            if (list->redirects->append_file[i + 1] != NULL)
                close(tmp_fd);
            else
                list->fd_out = tmp_fd;
            i++;
        }
    }
	return(set_redirections_two(list));
}

int set_redirections_two(t_com *list)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 0;
	if (list->redirects == NULL)
		return(0);
	if (list->redirects->redirect_heredoc) // Heredoc toma prioridad sobre otras redirecciones de input
    	return(heredoc_execution(list), list->redirects->redirected = 1, 1);
	else if (list->redirects->redirect_in && list->redirects->input_file)
	{
		while(list->redirects->redirect_in && list->redirects->input_file[i + 1]) //list->redirects->redirect_in Esto se comprueba antes?
			i++; // esto es para recorrer la matriz de cada redirección
		list->fd_in = open(list->redirects->input_file[i], O_RDONLY);
		if (list->fd_in == -1)
			return(write(2, "minishell: ", 11), perror(list->redirects->input_file[i]), 0);
	}
	if (list->redirects->redirect_out && list->redirects->output_file)
	{
		while (list->redirects->redirect_out && list->redirects->output_file[j + 1]) // Encontrar el ultimo archivo de output
			j++;
		if (list->fd_out != STDOUT_FILENO) // > sobrescribe >> si hay ambos
			close(list->fd_out);
		list->fd_out = open(list->redirects->output_file[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (list->fd_out == -1)
            return(write(2, "minishell: ", 11), perror(list->redirects->output_file[j]), list->fd_out = 1, 0);
	}
	if (list->redirects->redirect_append && list->redirects->append_file)
	{
		while(list->redirects->redirect_append && list->redirects->append_file[k + 1]) // Encontrar el ultimo archivo de append
			k++;
		list->fd_out = open(list->redirects->append_file[k], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (list->fd_out == -1)
			return(write(2, "minishell: ", 11), perror(list->redirects->append_file[k]), list->fd_out = 1, 0);
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
