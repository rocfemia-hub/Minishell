/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/04 20:28:52 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirections_control(t_com *list, int j, int q, int k)
{
	int	i;

	i = -1;
	if (list->redirects == NULL)
		return (0);
	if (list->redirects->redirected == 1)
		return (1);
	list->redirects->redirected = 1;
	if (list->redirects->redirect_heredoc)
	{
		heredoc_execution(list);
		if (g_signal == SIGINT)
			return (0);
		return (1);
	}
	while (list->redirects->t_red && list->redirects->t_red[++i] != 0)
	{
		if (list->redirects->t_red[i] == 1 && !infile_redirection(list, j++))
			return (0);
		if (list->redirects->t_red[i] == 2 && !outfile_redirection(list, q++))
			return (0);
		if (list->redirects->t_red[i] == 3 && !append_redirection(list, k++))
			return (0);
	}
	return (1);
}

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

void	heredoc_execution(t_com *list)
{
	char		*temp_file;
	int			fd;
	char		*num_str;
	static int	heredoc_count = 0;

	num_str = ft_itoa(heredoc_count++);
	temp_file = ft_strjoin("/tmp/.heredoc_", num_str);
	free(num_str);
	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror("heredoc");
		free(temp_file);
		return ;
	}
	found_delimiter(list, fd);
	close(fd);
	if (g_signal == SIGINT)
		return (unlink(temp_file), free(temp_file),
			list->vars->exit_status = 130, (void) 0);
	list->redirects->heredoc_file = temp_file;
	list->fd_in = open(temp_file, O_RDONLY, 0777);
}

char	*read_line_heredoc(void)
{
	char	*line;
	char	buffer[1000];
	char	c;
	int		i;
	int		ret;

	i = 0;
	ft_putstr_fd("> ", 1);
	while (i < 999)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret <= 0 || g_signal == SIGINT)
			break ;
		if (c == '\n')
			break ;
		buffer[i] = c;
		i++;
	}
	if (i == 0 && (ret <= 0 || g_signal == SIGINT))
		return (NULL);
	return (buffer[i] = '\0', line = ft_strdup(buffer), line);
}

void	found_delimiter(t_com *list, int fd)
{
	char	*line;

	setup_signals_heredoc();
	g_signal = 0;
	while (1)
	{
		line = read_line_heredoc();
		if (g_signal == SIGINT)
		{
			if (line)
				free(line);
			setup_signals_interactive();
			restore_terminal_heredoc();
			return ;
		}
		if (!line)
		{
			if (g_signal == SIGINT)
			{
				setup_signals_interactive();
				restore_terminal_heredoc();
				return ;
			}
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(list->redirects->delimiter, 2);
			ft_putstr_fd("')\n", 2);
			list->vars->exit_status = 0;
			break ;
		}
		if (ft_strncmp(line, list->redirects->delimiter, ft_strlen(list->redirects->delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}

	setup_signals_interactive();
	restore_terminal_heredoc();
	return ;
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
	if (list->previous && list->previous->redirects->err && !list->redirects->redirect_in)
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
