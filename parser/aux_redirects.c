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
	if (!commands->args[commands->redirects->j])
		return (1);
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

static char	*extract_until_redirect(char *str, char **rest)
{
	int		len;
	char	*file;
	char	*trimmed;

	len = 0;
	while (str[len] && str[len] != '<' && str[len] != '>')
		len++;
	trimmed = ft_substr(str, 0, len);
	file = ft_strtrim(trimmed, " \t");
	free(trimmed);
	if (str[len])
	{
		while (str[len] && (str[len] == ' ' || str[len] == '\t'))
			len++;
		*rest = ft_strdup(str + len);
	}
	else
		*rest = NULL;
	return (file);
}

void redirects_aux(t_com *commands, char *rest)
{
	char *tmp;
	char *trimmed;

	commands->args = copy_redirect_matrix(commands->args,
										  commands->redirects->j, commands->redirects->j);
	if (rest)
	{
		tmp = commands->args[commands->redirects->j];
		trimmed = ft_strtrim(rest, " \t");
		commands->args[commands->redirects->j] = trimmed;
		if (tmp)
			free(tmp);
		free(rest);
	}
}

void aux_redirects(t_com *commands, char *redirect_pos, int type,
				   char *redirect)
{
	char *tmp_file;
	char *rest;
	char *tmp;
	int pos;

	tmp_file = extract_until_redirect(redirect_pos + ft_strlen(redirect), &rest);
	pos = redirect_pos - commands->args[commands->redirects->j];
	if (pos > 0)
	{
		tmp = commands->args[commands->redirects->j];
		commands->args[commands->redirects->j] = ft_substr(tmp, 0, pos);
		(free(tmp), free(rest));
	}
	else
		redirects_aux(commands, rest);
	fill_type_redirect(commands, type);
	fill_red(commands, redirect, tmp_file);
}
