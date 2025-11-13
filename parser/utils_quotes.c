/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 01:12:07 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	look_for_char(char *line, char c)
{
	int		i;
	int		count;
	char	open_quote;

	i = 0;
	count = 0;
	open_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!open_quote)
				open_quote = line[i];
			else if (line[i] == open_quote)
				open_quote = 0;
		}
		else if (line[i] == c && !open_quote)
			count++;
		i++;
	}
	if (open_quote != 0)
		return (-1);
	return (count);
}

int	has_redirects(char *line)
{
	if (ft_strnstr(line, "<", ft_strlen(line)) || ft_strnstr(line, "<<",
			ft_strlen(line)) || ft_strnstr(line, ">", ft_strlen(line))
		|| ft_strnstr(line, ">>", ft_strlen(line)))
		return (1);
	return (0);
}

char	**ft_strjoin_cmd_arg(t_com *commands)
{
	int		j;
	int		len;
	char	**aux;
	int		i;

	j = -1;
	i = 0;
	len = 0;
	if (commands->command)
		len = 1;
	if (commands->args)
		while (commands->args[++j])
			len++;
	aux = ft_calloc(len + 1, sizeof(char *));
	if (commands->command)
		aux[i++] = ft_strdup(commands->command);
	j = -1;
	if (commands->args)
		while (commands->args[++j])
			aux[i++] = ft_strdup(commands->args[j]);
	return (aux);
}

void	quotes_for_redir(char **arg, int *k, int start, char q)
{
	int	m;

	m = *k;
	while (m > start)
	{
		(*arg)[m] = (*arg)[m - 1];
		m--;
	}
	(*arg)[start] = q;
	(*arg)[*k + 1] = q;
	*k += 2;
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
