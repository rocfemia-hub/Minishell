/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:59:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_cmd(t_com *commands, char *redirect, char *file)
{
	if (ft_strncmp(redirect, "<", 2) == 0)
		handle_redirect_array(&commands->redirects->input_file, &commands->redirects->redirect_in, file, commands);
	else if (ft_strncmp(redirect, ">", 2) == 0)
		handle_redirect_array(&commands->redirects->output_file, &commands->redirects->redirect_out, file, commands);
	else if (ft_strncmp(redirect, ">>", 3) == 0)
		handle_redirect_array(&commands->redirects->append_file, &commands->redirects->redirect_append, file, commands);
	else if (ft_strncmp(redirect, "<<", 3) == 0)
	{
		commands->redirects->delimiter = clean_quotes_in_line(ft_strdup(file));
		commands->redirects->redirect_heredoc = 1;
	}
	free(file);
}

void	aux_clean_redirects_cmd(t_com *commands, char *redirect, int type)
{
	char	*tmp_file;
	int		i;
	char	*tmp_cmd;

	i = 0;
	if (ft_strlen(commands->command) > ft_strlen(redirect))
	{
		while (commands->command[i] && ft_strncmp(commands->command + i, redirect, ft_strlen(redirect)) != 0)
			i++;
		tmp_file = ft_strdup(commands->command + i + ft_strlen(redirect));
		fill_cmd(commands, redirect, tmp_file);
		fill_type_redirect(commands, type);
		tmp_cmd = commands->command;
		commands->command = ft_substr(tmp_cmd, 0, i);
		free(tmp_cmd);
	}
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

int	clean_redirects_cmd(t_com *commands, char *redirect, int type)
{
	if (ft_strnstr(commands->command, ">>>", 3))
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strnstr(commands->command, "<<<", 3))
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else
		aux_clean_redirects_cmd(commands, redirect, type);
	return (1);
}

int	aux_redirects_cmd(t_com *commands)
{
	if (commands->args[0] || ft_strlen(commands->command) > 2)
	{
		if (is_redirect_token(commands->command, "<<"))
			if (!clean_redirects_cmd(commands, "<<", 4))
				return (0);
		if (is_redirect_token(commands->command, ">>"))
			if (!clean_redirects_cmd(commands, ">>", 3))
				return (0);
		look_for_cmd(commands);
		return (1);
	}
	else
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
}

int	redirects_cmd(t_com *commands)
{
	if (is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">>"))
	{
		if (!aux_redirects_cmd(commands))
			return (0);
	}
	if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, ">"))
	{
		if (commands->args[0] || ft_strlen(commands->command) > 1)
		{
			if (is_redirect_token(commands->command, "<"))
				clean_redirects_cmd(commands, "<", 1);
			if (is_redirect_token(commands->command, ">"))
				clean_redirects_cmd(commands, ">", 2);
			look_for_cmd(commands);
			return (1);
		}
		else
		{
			commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
			commands->vars->exit_status = 2;
			return (0);
		}
	}
	return (0);
}
