/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:04 by roo               #+#    #+#             */
/*   Updated: 2025/11/04 15:56:09 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*only_cmd(char *line, t_clean_cmd *data)
{
	data->only_cmd_i += skip_spaces(&line[data->only_cmd_i]);
	while (line[data->only_cmd_i] == '\n')
		data->only_cmd_i++;
	data->quote = 0;
	if (!line[data->only_cmd_i])
		return (NULL);
	data->start = data->only_cmd_i;
	while (line[data->only_cmd_i])
	{
		if (line[data->only_cmd_i] == '\'' || line[data->only_cmd_i] == '"')
			aux_only_cmd(line, data);
		if (data->quote == 0 && line[data->only_cmd_i] == ' ')
		{
			data->end = data->only_cmd_i;
			break ;
		}
		data->only_cmd_i++;
	}
	if (!line[data->only_cmd_i])
		data->end = data->only_cmd_i;
	return (ft_substr(line, data->start, data->end - data->start));
}

static void	handle_no_expansion(char *line, t_clean_cmd *data, t_com *commands)
{
	char	*temp;

	free(data->cmd);
	data->cmd = only_cmd(line, data);
	if (data->cmd)
	{
		temp = data->cmd;
		data->cmd = clean_cmd(data->cmd);
		free(temp);
		init_struct(line, data->cmd, data->only_cmd_i, commands);
	}
}

void	type_command(char *line, t_com *commands)
{
	t_clean_cmd	data;
	char		*temp;
	int			saved_index;

	ft_bzero(&data, sizeof(t_clean_cmd));
	data.cmd = only_cmd(line, &data);
	if (!data.cmd)
		return ;
	saved_index = data.only_cmd_i;
	if (ft_strnstr(data.cmd, "$", ft_strlen(data.cmd)))
	{
		if (expand_cmd(&data, commands->vars))
			init_struct(line, data.cmd, saved_index, commands);
		else
			handle_no_expansion(line, &data, commands);
	}
	else
	{
		temp = data.cmd;
		data.cmd = clean_cmd(data.cmd);
		free(temp);
		init_struct(line, data.cmd, saved_index, commands);
	}
	free(data.cmd);
}

void	init_commands(char *line, t_com *commands)
{
	int		i;
	int		start;
	char	quote;
	t_com	*current;

	i = -1;
	start = 0;
	quote = 0;
	current = commands;
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\''))
			handle_quote(line[i], &quote);
		if (line[i] == '|' && !quote)
		{
			line[i] = '\0';
			type_command(line + start, current);
			start = i + 1;
			current = current->next;
		}
	}
	if (current)
		type_command(line + start, current);
}

t_com	*token(char *line, t_vars *vars)
{
	t_com	*commands;

	commands = NULL;
	if (validate_syntax(line))
	{
		vars->exit_status = 2;
		return (NULL);
	}
	commands = create_struct(line, vars);
	commands->vars = vars;
	if (commands->error)
	{
		error(commands);
		return (NULL);
	}
	init_commands(line, commands);
	if (commands->error)
	{
		error(commands);
		return (NULL);
	}
	return (commands);
}
