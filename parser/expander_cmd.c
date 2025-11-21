/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:34 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 02:52:28 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar_in_quotes(char *line, int *k, int *start, t_vars *vars)
{
	char	*tmp;
	char	*token;

	token = NULL;
	if (*k > *start)
	{
		tmp = ft_substr(line, *start, *k - *start);
		token = str_append(token, tmp);
		free(tmp);
	}
	*start = *k;
	token = expand_var_in_quotes_args(line, k, token, vars);
	*start = *k;
	return (token);
}

char	*str_append(char *dest, const char *src)
{
	char	*tmp;

	if (!dest)
		dest = ft_strdup(src);
	else
	{
		tmp = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, dest, ft_strlen(dest) + 1);
		ft_strlcat(tmp, src, ft_strlen(tmp) + ft_strlen(src) + 1);
		free(dest);
		dest = tmp;
	}
	return (dest);
}

char	*handle_plain_text(char *cmd, int *i, t_vars *vars)
{
	int	start;

	if (!vars)
		return (NULL);
	start = *i;
	while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '"' && cmd[*i] != '$')
		(*i)++;
	return (ft_substr(cmd, start, *i - start));
}

char	*aux_cmd(t_clean_cmd *data, t_vars *vars)
{
	int		i;
	char	*token;
	char	*result;

	i = 0;
	result = NULL;
	while (data->cmd[i])
	{
		if (data->cmd[i] == '\'')
			token = handle_single_quotes(data->cmd, &i, vars);
		else if (data->cmd[i] == '"')
			token = handle_double_quotes(data->cmd, &i, vars);
		else if (data->cmd[i] == '$')
			token = handle_dollar(data->cmd, &i, vars);
		else if (data->cmd[i] == '~')
			token = handle_tilde(data->cmd, &i, vars);
		else
			token = handle_plain_text(data->cmd, &i, vars);
		if (token)
		{
			result = str_append(result, token);
			free(token);
		}
	}
	return (result);
}

int	expand_cmd(t_clean_cmd *data, t_vars *vars, t_com *commands)
{
	char		*expanded;
	t_clean_cmd	temp_data;

	expanded = aux_cmd(data, vars);
	free(data->cmd);
	data->cmd = expanded;
	if (!expanded)
		return (0);
	ft_bzero(&temp_data, sizeof(t_clean_cmd));
	if (!ft_strlen(expanded))
		temp_data.cmd = ft_strdup(expanded);
	else
		temp_data.cmd = only_cmd(expanded, &temp_data, &commands->quoted);
	init_struct(expanded, temp_data.cmd, temp_data.only_cmd_i, commands);
	free(temp_data.cmd);
	return (1);
}
