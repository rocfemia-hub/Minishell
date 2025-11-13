/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:19 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 01:00:41 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_arg_quotes(char *arg, char *new_arg)
{
	int		j;
	int		k;
	char	quote;

	j = 0;
	k = 0;
	quote = 0;
	while (arg[j])
	{
		if ((arg[j] == '\'' || arg[j] == '"') && !quote)
			quote = arg[j++];
		else if (quote && arg[j] == quote)
		{
			quote = 0;
			j++;
		}
		else
			new_arg[k++] = arg[j++];
	}
	new_arg[k] = '\0';
}

void	clean_reinserted_quotes_in_args(t_com *commands)
{
	int		i;
	char	*arg;
	char	*new_arg;
	int		len;

	i = 0;
	while (commands->args && commands->args[i])
	{
		arg = commands->args[i];
		len = ft_strlen(arg);
		new_arg = ft_calloc(len + 1, sizeof(char));
		if (!new_arg)
			return ;
		process_arg_quotes(arg, new_arg);
		free(commands->args[i]);
		commands->args[i] = new_arg;
		i++;
	}
}

static void	process_quote_char_clean(char *temp, char *result, int *j, int *k)
{
	static char	quote;

	if (temp[*j] == '\'' || temp[*j] == '"')
	{
		if (!quote)
			quote = temp[(*j)++];
		else if (quote == temp[*j])
		{
			quote = 0;
			(*j)++;
		}
		else
			result[(*k)++] = temp[(*j)++];
	}
	else
		result[(*k)++] = temp[(*j)++];
}

static char	*remove_quotes_from_cmd(char *temp)
{
	char	*result;
	int		j;
	int		k;

	result = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	if (!result)
		return (free(temp), NULL);
	j = 0;
	k = 0;
	while (temp[j])
		process_quote_char_clean(temp, result, &j, &k);
	result[k] = '\0';
	free(temp);
	return (result);
}

char	*clean_cmd(char *line)
{
	char	*temp;

	if (has_redirects(line))
		return (ft_strdup(line));
	if (!line)
		return (NULL);
	temp = ft_strdup(line);
	if (!temp)
		return (NULL);
	return (remove_quotes_from_cmd(temp));
}
