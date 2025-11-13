/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 16:48:40 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	aux_parser_redirects(t_com *commands, char *redirect, int type)
{
	char	*tmp_file;

	if (!commands->args[commands->redirects->j + 1])
	{
		commands->error = ft_strdup("near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1)
		|| ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1))
	{
		if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1))
			commands->error = ft_strdup("near unexpected token `>'");
		else if (ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1))
			commands->error = ft_strdup("near unexpected token `<'");
		commands->vars->exit_status = 2;
		return (0);
	}
	tmp_file = ft_strdup(commands->args[commands->redirects->j + 1]);
	fill_type_redirect(commands, type);
	commands->args = copy_redirect_matrix(commands->args,
			commands->redirects->j, commands->redirects->j + 1);
	fill_red(commands, redirect, tmp_file);
	return (1);
}

int parser_redirects(t_com *commands, char *redirect, int type)
{
	char *tmp_file;
	char *redirect_pos;

	if (!commands->args[commands->redirects->j])
		return (1);
	else if (ft_strlen(commands->args[commands->redirects->j]) > ft_strlen(redirect))
	{
		redirect_pos = find_redirect_position(
			commands->args[commands->redirects->j], redirect);
		if (redirect_pos)
			aux_redirects(commands, redirect_pos, type, redirect);
		else
		{
			tmp_file = ft_strdup(commands->args[commands->redirects->j] + ft_strlen(redirect));
			fill_type_redirect(commands, type);
			commands->args = copy_redirect_matrix(commands->args,
												  commands->redirects->j, commands->redirects->j);
			fill_red(commands, redirect, tmp_file);
		}
	}
	else if (!aux_parser_redirects(commands, redirect, type))
		return (0);
	return (1);
}

int aux_find(t_com *commands, char **pos, char *first)
{
	int i;
	int first_idx;

	first_idx = -1;
	i = -1;
	while (++i < 4)
	{
		if (pos[i] && (!first || pos[i] < first || (pos[i] == first && i > first_idx)))
		{
			first = pos[i];
			first_idx = i;
		}
	}
	if (!first)
		return (1);
	if (first_idx == 2 && !parser_redirects(commands, "<<", 4))
		return (0);
	else if (first_idx == 3 && !parser_redirects(commands, ">>", 3))
		return (0);
	else if (first_idx == 0 && !parser_redirects(commands, "<", 1))
		return (0);
	else if (first_idx == 1 && !parser_redirects(commands, ">", 2))
		return (0);
	commands->redirects->j = -1;
	return (1);
}

void find(t_com *commands)
{
	char *pos[4];
	char *first;

	first = NULL;
	if (!commands->args || !commands->redirects || commands->redirects->j)
		return;
	while (commands->args[commands->redirects->j])
	{
		pos[0] = find_redirect_position(commands->args[commands->redirects->j], "<");
		pos[1] = find_redirect_position(commands->args[commands->redirects->j], ">");
		pos[2] = find_redirect_position(commands->args[commands->redirects->j], "<<");
		pos[3] = find_redirect_position(commands->args[commands->redirects->j], ">>");
		if (!aux_find(commands, pos, first))
			return;
		commands->redirects->j++;
	}
}

void redirects(t_com *commands)
{
	char *temp;

	commands->redirects = ft_calloc(1, sizeof(t_red));
	if (!commands->redirects)
		return;
	if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">") || is_redirect_token(commands->command, ">>"))
	{
		if (!redirects_cmd(commands))
			return;
	}
	else
	{
		temp = clean_quotes_in_line(commands->command);
		commands->command = ft_strdup(temp);
		free(temp);
	}
	find(commands);
}
