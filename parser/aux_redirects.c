/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 01:34:35 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirect(char c)
{
	return (c == '<' || c == '>');
}

char *find_redirect_position(char *arg, char *redirect)
{
	int i;
	int quote;

	i = 0;
	quote = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (quote == 0)
				quote = arg[i];
			else if (quote == arg[i])
				quote = 0;
		}
		else if (!quote && ft_strncmp(arg + i, redirect,
									  ft_strlen(redirect)) == 0)
			return (arg + i);
		i++;
	}
	return (NULL);
}

int is_redirect_token(char *arg, char *redirect)
{
	int i;
	int quote;

	i = 0;
	quote = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (quote == 0)
				quote = arg[i];
			else if (quote == arg[i])
				quote = 0;
		}
		else if (!quote && ft_strncmp(arg + i, redirect,
									  ft_strlen(redirect)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int aux_parser_resdirects_sintax_error(t_com *commands)
{
	if (ft_strnstr(commands->args[commands->redirects->j], ">>>", 3))
	{
		commands->error = ft_strdup("near unexpected token `>'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strnstr(commands->args[commands->redirects->j], "<<<", 3))
	{
		commands->error = ft_strdup("near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	return (1);
}

void aux_redirects(t_com *commands, char *redirect_pos, int type,
				   char *redirect)
{
	char *tmp_file;
	int pos;
	char *before_redirect;

	pos = 0;
	tmp_file = ft_strdup(redirect_pos + ft_strlen(redirect));
	pos = redirect_pos - commands->args[commands->redirects->j];
	if (pos > 0)
	{
		before_redirect = ft_calloc(pos + 1, sizeof(char));
		ft_strlcpy(before_redirect, commands->args[commands->redirects->j], pos + 1);
		free(commands->args[commands->redirects->j]);
		commands->args[commands->redirects->j] = before_redirect;
		fill_type_redirect(commands, type);
		fill_red(commands, redirect, tmp_file);
	}
	else
	{
		fill_type_redirect(commands, type);
		commands->args = copy_redirect_matrix(commands->args,
											  commands->redirects->j, commands->redirects->j);
		fill_red(commands, redirect, tmp_file);
	}
}
