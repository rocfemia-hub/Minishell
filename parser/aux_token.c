/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/04 15:56:09 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	return (i);
}

void	aux_only_cmd(char *line, t_clean_cmd *data)
{
	if (!data->quote)
		data->quote = line[data->only_cmd_i];
	else if (data->quote == line[data->only_cmd_i])
		data->quote = 0;
}

void	handle_quote(char c, char *quote)
{
	if (!(*quote))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

void	process_quote_char(char current_char, char *new_arg, int *k,
		char *quote)
{
	if (*quote == 0)
		*quote = current_char;
	else if (*quote == current_char)
		*quote = 0;
	else
		new_arg[(*k)++] = current_char;
}

char	*clean_quotes_in_line(char *arg)
{
	int		j;
	int		k;
	char	*new_arg;
	char	quote;

	if (!arg)
		return (NULL);
	new_arg = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!new_arg)
		return (NULL);
	j = 0;
	k = 0;
	quote = 0;
	while (arg[j])
	{
		if (arg[j] == '\'' || arg[j] == '"')
			process_quote_char(arg[j], new_arg, &k, &quote);
		else
			new_arg[k++] = arg[j];
		j++;
	}
	new_arg[k] = '\0';
	free(arg);
	return (new_arg);
}
