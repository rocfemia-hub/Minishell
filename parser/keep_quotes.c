/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 03:39:59 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	flush_buffer(char *arg, int flush, char **args, int *j)
{
	if (flush)
	{
		args[(*j)++] = ft_strdup(arg);
		arg[0] = '\0';
	}
}

static void	add_redir_token(char *line, int *i, char **args, int *j)
{
	if (line[*i + 1] == line[*i])
	{
		args[(*j)++] = ft_strdup((char [3]){line[*i], line[*i], '\0'});
		*i += 2;
	}
	else
	{
		args[(*j)++] = ft_strdup((char [2]){line[*i], '\0'});
		(*i)++;
	}
}

void	process_single_word(char *line, int *i, char **args, int *j)
{
	char	*arg;
	int		k;
	int		is_word;

	arg = ft_calloc(ft_strlen(line) + 3, sizeof(char));
	if (!arg)
		return ;
	k = 0;
	is_word = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
	{
		if (line[*i] == '<' || line[*i] == '>')
		{
			k = 0;
			flush_buffer(arg, (k > 0 || is_word), args, j);
			add_redir_token(line, i, args, j);
			continue ;
		}
		is_word = 1;
		if (line[*i] == '\'' || line[*i] == '"')
			aux_keep_quotes_args(line, i, &k, &arg);
		else
			arg[k++] = line[(*i)++];
	}
	(flush_buffer(arg, (k > 0 || is_word), args, j), free(arg));
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
