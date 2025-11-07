/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/07 14:57:27 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_redirection(t_com *list, int i)
{
	int	tmp_fd;

	if (list->redirects->redirect_in && list->redirects->input_file)
	{
		tmp_fd = open(list->redirects->input_file[i], O_RDONLY);
		if (tmp_fd == -1)
			return (write(2, "minishell: ", 11),
				perror(list->redirects->input_file[i]), 0);
		if (list->fd_in != 0)
			close(list->fd_in);
		list->fd_in = tmp_fd;
	}
	return (1);
}

int	outfile_redirection(t_com *list, int i)
{
	int	tmp_fd;

	if (list->redirects->output_file && list->redirects->output_file[i])
	{
		tmp_fd = open(list->redirects->output_file[i],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (tmp_fd == -1)
			return (write(2, "minishell: ", 11),
				perror(list->redirects->output_file[i]), 0);
		if (list->fd_out != 1)
			close(list->fd_out);
		list->fd_out = tmp_fd;
	}
	return (1);
}

int	append_redirection(t_com *list, int i)
{
	int	tmp_fd;

	if (list->redirects->append_file && list->redirects->append_file[i])
	{
		tmp_fd = open(list->redirects->append_file[i],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (tmp_fd == -1)
			return (write(2, "minishell: ", 11),
				perror(list->redirects->append_file[i]), 0);
		if (list->fd_out != 1)
			close(list->fd_out);
		list->fd_out = tmp_fd;
	}
	return (1);
}

void	apply_redirections(t_com *list)
{
	if (list->fd_in != STDIN_FILENO)
	{
		if (dup2(list->fd_in, STDIN_FILENO) == -1)
		{
			write(2, "minishell: ", 11);
			perror("dup2 stdin");
			exit(1);
		}
		close(list->fd_in);
		list->fd_in = 0;
	}
	if (list->fd_out != STDOUT_FILENO)
	{
		if (dup2(list->fd_out, STDOUT_FILENO) == -1)
		{
			write(2, "minishell: ", 11);
			perror("dup2 stdout");
			exit(1);
		}
		close(list->fd_out);
		list->fd_out = 1;
	}
	if (list->previous && list->previous->redirects->err
		&& !list->redirects->redirect_in)
		close(list->fd_in);
}

void	clean_fds(t_com *list)
{
	if (list->fd_in != STDIN_FILENO)
		close(list->fd_in);
	if (list->fd_out != STDOUT_FILENO)
	{
		close(list->fd_out);
	}
	list->fd_in = STDIN_FILENO;
	list->fd_out = STDOUT_FILENO;
	if (list->redirects && list->redirects->heredoc_file)
	{
		unlink(list->redirects->heredoc_file);
		free(list->redirects->heredoc_file);
		list->redirects->heredoc_file = NULL;
	}
}
