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

char	*ft_strjoin_cmd(char **cmd)
{
	int		len;
	char	*result;
	int		i;

	len = 0;
	i = -1;
	if (!cmd || !cmd[0])
		return (NULL);
	while (cmd[++i])
		len += ft_strlen(cmd[i]);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = -1;
	while (cmd[++i])
		ft_strlcat(result, cmd[i], ft_strlen(result) + ft_strlen(cmd[i]) + 1);
	return (result);
}

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

char	**process_aux_args(char **args, char **token_args, t_vars *vars)
{
	int		i;
	int		j;
	int		k;
	char	*token;
	char	*accumulated;

	i = -1;
	j = 0;
	while (args[++i])
	{
		k = 0;
		accumulated = NULL;
		while (args[i][k])
		{
			if (args[i][k] == '\'')
				token = handle_single_quotes(args[i], &k, vars);
			else if (args[i][k] == '"')
				token = handle_double_quotes(args[i], &k, vars);
			else if (args[i][k] == '$')
				token = handle_dollar(args[i], &k, vars);
			else
				token = handle_plain_text_args(args[i], &k, vars);
			if (token)
			{
				accumulated = str_append(accumulated, token);
				free(token);
			}
		}
		if (accumulated)
			token_args[j++] = accumulated;
	}
	token_args[j] = NULL;
	return (token_args);
}

void	expand_args(t_com *commands)
{
	char	**token_args;
	char	**old_args;

	if(commands->redirects && commands->redirects->redirect_heredoc != 0)
		return;
	token_args = ft_calloc((256 + 1), sizeof(char *));
	if (!token_args)
		return ;
	old_args = commands->args;
	token_args = process_aux_args(commands->args, token_args, commands->vars);
	commands->args = token_args;
	commands->expanded = 1;  // marcar que ya se expandió
	if (old_args)
		ft_free_free(old_args);
}
