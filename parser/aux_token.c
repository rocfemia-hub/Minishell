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
