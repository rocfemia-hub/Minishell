/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:30 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 07:01:28 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_plain_text_args(char *line, int *i, t_vars *vars)
{
	int		start;
	char	*token;

	if (!vars)
		return (NULL);
	token = NULL;
	start = *i;
	while (line[*i] && line[*i] != '\'' && line[*i] != '"' && line[*i] != '$')
		(*i)++;
	token = ft_substr(line, start, *i - start);
	return (token);
}

char	*process_single_arg(char *arg, t_vars *vars)
{
	char	*token;
	char	*accumulated;
	int		k;

	accumulated = NULL;
	k = 0;
	while (arg[k])
	{
		if (arg[k] == '\'')
			token = handle_single_quotes(arg, &k, vars);
		else if (arg[k] == '"')
			token = handle_double_quotes(arg, &k, vars);
		else if (arg[k] == '$')
			token = handle_dollar(arg, &k, vars);
		else
			token = handle_plain_text_args(arg, &k, vars);
		if (token)
		{
			accumulated = str_append(accumulated, token);
			free(token);
		}
	}
	return (accumulated);
}

static void	process_and_add_arg(char *arg, char **token_args, int *j,
		t_vars *vars)
{
	char	*accumulated;
	int		had_quotes;

	had_quotes = (ft_strchr(arg, '\'') || ft_strchr(arg, '"'));
	accumulated = process_single_arg(arg, vars);
	if (accumulated && ft_strlen(accumulated) > 0)
	{
		if (!had_quotes && ft_strchr(arg, '$'))
		{
			add_split_args(token_args, j, accumulated);
			free(accumulated);
		}
		else
			token_args[(*j)++] = accumulated;
	}
	else if (accumulated && had_quotes)
		token_args[(*j)++] = accumulated;
	else if (accumulated)
		free(accumulated);
}

char	**process_aux_args(char **args, char **token_args, t_vars *vars)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (args[++i])
		process_and_add_arg(args[i], token_args, &j, vars);
	token_args[j] = NULL;
	return (token_args);
}

void	expand_args(t_com *commands)
{
	char	**token_args;
	char	**old_args;

	if (commands->redirects && commands->redirects->redirect_heredoc != 0)
		return ;
	token_args = ft_calloc((256 + 1), sizeof(char *));
	if (!token_args)
		return ;
	old_args = commands->args;
	token_args = process_aux_args(commands->args, token_args, commands->vars);
	commands->args = token_args;
	commands->expanded = 1;
	if (old_args)
		ft_free_free(old_args);
}
