/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 03:10:59 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 03:39:48 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	skip_whitespace(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	check_pipe_syntax(char *line, int i, char quote)
{
	int	j;

	if (quote)
		return (0);
	if (i == 0)
		return (1);
	j = i + 1;
	if (line[j] == '|')
	{
		j++;
		if (line[j] == '|')
			return (1);
	}
	j = skip_whitespace(line, j);
	if (!line[j] || line[j] == '|')
		return (1);
	return (0);
}
