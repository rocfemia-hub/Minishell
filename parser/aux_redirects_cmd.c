/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:59:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_command_redirect(t_com *commands, char *redirect, int type)
{
	char	*tmp_file;
	int		i;
	char	*tmp_cmd;

	i = 0;
	while (commands->command[i] && ft_strncmp(commands->command + i,
			redirect, ft_strlen(redirect)) != 0)
		i++;
	tmp_file = ft_strdup(commands->command + i + ft_strlen(redirect));
	fill_cmd(commands, redirect, tmp_file);
	fill_type_redirect(commands, type);
	tmp_cmd = commands->command;
	commands->command = ft_substr(tmp_cmd, 0, i);
	free(tmp_cmd);
}

void	aux_clean_redirects_cmd(t_com *commands, char *redirect, int type)
{
	char	*tmp_file;

	if (ft_strlen(commands->command) > ft_strlen(redirect))
		handle_command_redirect(commands, redirect, type);
	else if (commands->args[0])
	{
		tmp_file = ft_strdup(commands->args[0]);
		fill_cmd(commands, redirect, tmp_file);
		free(commands->command);
		commands->command = ft_strdup("");
		commands->args = realloc_redirect_args(commands->args);
		fill_type_redirect(commands, type);
	}
}

void	fill_cmd(t_com *commands, char *redirect, char *file)
{
	if (ft_strncmp(redirect, "<", 2) == 0)
		handle_redirect_array(&commands->redirects->input_file,
			&commands->redirects->redirect_in, file, commands);
	else if (ft_strncmp(redirect, ">", 2) == 0)
		handle_redirect_array(&commands->redirects->output_file,
			&commands->redirects->redirect_out, file, commands);
	else if (ft_strncmp(redirect, ">>", 3) == 0)
		handle_redirect_array(&commands->redirects->append_file,
			&commands->redirects->redirect_append, file, commands);
	else if (ft_strncmp(redirect, "<<", 3) == 0)
	{
		commands->redirects->delimiter = clean_quotes_in_line(ft_strdup(file));
		commands->redirects->redirect_heredoc = 1;
	}
	free(file);
}

char	**realloc_redirect_args(char **flag)
{
	int		i;
	int		j;
	char	**realloc_matrix;

	j = 0;
	while (flag[j])
		j++;
	realloc_matrix = ft_calloc(j, sizeof(char *));
	if (!realloc_matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (flag[++i])
	{
		realloc_matrix[j] = ft_strdup(flag[i]);
		j++;
	}
	ft_free_free(flag);
	return (realloc_matrix);
}

void	look_for_cmd(t_com *commands)
{
	char	**temp;
	int		i;

	i = -1;
	if (!commands || !commands->args)
		return ;
	while (commands->args[++i])
	{
		if (is_redirect_token(commands->args[i], "<<")
			|| is_redirect_token(commands->args[i], ">>")
			|| is_redirect_token(commands->args[i], "<")
			|| is_redirect_token(commands->args[i], ">"))
			find(commands);
	}
	if (!commands->command || ft_strlen(commands->command) < 1)
	{
		if (commands->args[0])
		{
			if (commands->command)
				free(commands->command);
			commands->command = ft_strdup(commands->args[0]);
			temp = realloc_redirect_args(commands->args);
			commands->args = temp;
		}
	}
}
