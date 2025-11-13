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
//se cambian a estaticas
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

static int	check_redir_in_quotes(char *arg, int start, int end)
{
	int	t;

	t = start;
	while (t < end)
	{
		if (arg[t] == '>' || arg[t] == '<')
			return (1);
		t++;
	}
	return (0);
}

int	has_redirects(char *line)
{
	if (ft_strnstr(line, "<", ft_strlen(line))
		|| ft_strnstr(line, "<<", ft_strlen(line))
		|| ft_strnstr(line, ">", ft_strlen(line))
		|| ft_strnstr(line, ">>", ft_strlen(line)))
		return (1);
	return (0);
}

void	copy_without_quotes(char *arg, char *new_arg, int *j, int *k)
{
	char	q;
	int		m;
	int		u;

	q = arg[*j];
	m = *j + 1;
	while (arg[m] && arg[m] != q)
		m++;
	if (arg[m] == q && check_redir_in_quotes(arg, *j + 1, m))
	{
		u = *j + 1;
		while (u < m)
			new_arg[(*k)++] = arg[u++];
		*j = m + 1;
		return ;
	}
	if (arg[m] == q)
	{
		new_arg[(*k)++] = arg[(*j)++];
		while (*j <= m)
			new_arg[(*k)++] = arg[(*j)++];
		return ;
	}
	new_arg[(*k)++] = arg[(*j)++];
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
	j = -1; //esto se hace siempreporque si no igual ya se ha modificado
	if (commands->args)
		while (commands->args[++j])
			aux[i++] = ft_strdup(commands->args[j]);
	return (aux);
}
