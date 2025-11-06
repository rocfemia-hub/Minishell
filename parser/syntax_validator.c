/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:00:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 00:00:00 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

static int	skip_whitespace(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

static int	check_pipe_syntax(char *line, int i, char quote)
{
	int	j;

	if (quote)
		return (0);
	j = i + 1;
	if (line[j] == '|')
	{
		j++;
		if (line[j] == '|')
			return (1);
	}
	j = skip_whitespace(line, j);
	if (!line[j] || line[j] == '|')
		return (1);
	return (0);
}

static int	check_redirect_pipe_mix(char *line, int i, char quote)
{
	int	j;

	if (quote)
		return (0);
	j = i + 1;
	if (is_redirect(line[i]) && line[j] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	if (line[i] == '|' && is_redirect(line[j]))
	{
		if (line[j] == '<')
			write(2, "minishell: syntax error near unexpected token `<'\n", 51);
		else
			write(2, "minishell: syntax error near unexpected token `>'\n", 51);
		return (1);
	}
	return (0);
}

int	validate_syntax(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (line[i] == '|' && check_pipe_syntax(line, i, quote))
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 51);
			return (1);
		}
		if ((line[i] == '|' || is_redirect(line[i]))
			&& check_redirect_pipe_mix(line, i, quote))
			return (1);
		i++;
	}
	return (0);
}
