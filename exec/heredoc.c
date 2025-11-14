/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:56:54 by roo               #+#    #+#             */
/*   Updated: 2025/11/07 19:56:39 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_line_heredoc(void)
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

static void	found_delimiter(t_com *list, int fd)
{
	char	*line;

	setup_signals_heredoc();
	g_signal = 0;
	while (1)
	{
		line = read_line_heredoc();
		if (line && g_signal == SIGINT)
			free(line);
		else if (!line && g_signal == SIGINT)
			return (setup_signals_interactive(), rest_termi_hrdc(), (void)0);
		else if (g_signal == SIGINT)
			return (setup_signals_interactive(), rest_termi_hrdc(), (void)0);
		else if (!line)
			return (write(STDOUT_FILENO, "\n", 1),
				ft_printf(2, "minishell: warning: here-document delimited by \
					end-of-file (wanted `%s')\n", list->redirects->delimiter),
				list->vars->exit_status = 0, setup_signals_interactive(),
				rest_termi_hrdc(), (void)0);
		if (ft_strncmp(line, list->redirects->delimiter,
				ft_strlen(list->redirects->delimiter) + 1) == 0)
			return (free(line), setup_signals_interactive(),
				rest_termi_hrdc(), (void)0);
		ft_printf(fd, "%s\n", line);
		free(line);
	}
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
