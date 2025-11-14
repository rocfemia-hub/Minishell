/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:00:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 19:22:40 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_syntax(char *line, int i, char quote)
{
	int	j;
	int	count;

	if (quote)
		return (0);
	if (i == 0)
		return (1);
	j = i + 1;
	count = 1;
	while (line[i] == line[j] || line[j] == ' ')
	{
		if (line[j++] == ' ')
			continue ;
		count++;
	}
	if (count > 1)
		return (1);
	return (0);
}

static void	aux_check_redirect_syntax(char *line, int j, char *buf)
{
	ft_strlcpy(buf, "newline", 8);
	if (line[j] == '|')
		ft_strlcpy(buf, "|", 2);
	else if (line[j] && line[j + 1])
	{
		if (line[j] == '<' && line[j + 1] == '<')
			ft_strlcpy(buf, "<<", 3);
		else if (line[j] == '<')
			ft_strlcpy(buf, "<", 2);
		else if (line[j] == '>' && line[j + 1] == '>')
			ft_strlcpy(buf, ">>", 3);
		else if (line[j] == '>')
			ft_strlcpy(buf, ">", 2);
	}
}

static int	check_redirect_syntax(char *line, int i, char quote)
{
	int		j;
	char	buf[8];

	if (quote)
		return (0);
	j = i + 1;
	if (line[i] == line[j])
		j++;
	j += skip_spaces(line + j);
	if (!line[j] || line[j] == '|' || is_redirect(line[j]))
	{
		ft_bzero(&buf, sizeof(char) * 8);
		aux_check_redirect_syntax(line, j, buf);
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, buf, ft_strlen(buf));
		write(2, "'\n", 2);
		return (1);
	}
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
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (1);
	}
	if (line[i] == '|' && is_redirect(line[j]))
	{
		if (line[j] == '<')
			write(2, "minishell: syntax error near unexpected token `<'\n", 50);
		else
			write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		return (1);
	}
	return (0);
}

int	validate_syntax(char *line)
{
	int		i;
	char	quote;

	quote = 0;
	i = skip_spaces(line);
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (line[i] == '|' && check_pipe_syntax(line, i, quote))
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			return (1);
		}
		if (is_redirect(line[i]) && check_redirect_syntax(line, i, quote))
			return (1);
		if ((line[i] == '|' || is_redirect(line[i]))
			&& check_redirect_pipe_mix(line, i, quote))
			return (1);
		i++;
	}
	return (0);
}
