/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/10/15 14:48:46 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	aux_keep_quotes_args(char *line, int *i, int *k, char **arg)
{
	int		start;
	char	q;

	q = line[(*i)++];
	start = *k;
	while (line[*i] && line[*i] != q)
		(*arg)[(*k)++] = line[(*i)++];
	if (line[*i] == q)
		(*i)++;
	if (ft_strchr(*arg + start, '>') || ft_strchr(*arg + start, '<'))
		quotes_for_redir(arg, k, start, q);
}

void	process_single_word(char *line, int *i, char **args, int *j)
{
	char	*arg;
	int		k;

	arg = ft_calloc(ft_strlen(line) + 3, sizeof(char));
	if (!arg)
		return ;
	k = 0;
	while (line[*i] && line[*i] != ' ')
	{
		if (line[*i] == '\'' || line[*i] == '"')
			aux_keep_quotes_args(line, i, &k, &arg);
		else
			arg[k++] = line[(*i)++];
	}
	arg[k] = '\0';
	args[(*j)++] = arg;
}

void	keep_quotes_args(t_com *commands, char *line)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	args = ft_calloc(sizeof(char *), ft_strlen(line) + 1);
	if (!args)
		return ;
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (!line[i])
			break ;
		process_single_word(line, &i, args, &j);
	}
	args[j] = NULL;
	commands->args = args;
}

