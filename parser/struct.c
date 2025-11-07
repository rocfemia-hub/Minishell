/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:51 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 17:39:00 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_strjoin_cmd_arg(t_com *commands)
{
	int		j;
	int		len;
	char	**aux;
	int		i;

	j = -1;
	i = 0;
	len = 0;
	if (commands->command)
		len = 1;
	if (commands->args)
		while (commands->args[++j])
			len++;
	aux = ft_calloc(len + 1, sizeof(char *));
	if (commands->command)
	{
		aux[i++] = ft_strdup(commands->command);
		j = -1;
	}
	if (commands->args)
		while (commands->args[++j])
			aux[i++] = ft_strdup(commands->args[j]);
	return (aux);
}

int	has_expandable_dollar(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!quote)
				quote = line[i];
			else if (line[i] == quote)
				quote = 0;
		}
		else if (line[i] == '$' && quote != '\'')
			return (1);
		i++;
	}
	return (0);
}

t_com	*create_error_struct(int i, t_vars *vars)
{
	t_com	*head;

	head = lstnew(i);
	head->error = ft_strdup("bash: open quote error");
	head->vars = vars;
	vars->exit_status = 1;
	return (head);
}

t_com	*create_struct(char *line, t_vars *vars)
{
	int		i;
	int		pipes;
	t_com	*new;
	t_com	*head;

	i = 0;
	pipes = look_for_char(line, 124);
	if (pipes < 0)
		return (create_error_struct(i, vars));
	head = lstnew(i);
	head->vars = vars;
	while (++i <= pipes)
	{
		new = lstnew(i);
		if (!new)
			return (NULL);
		new->vars = vars;
		lstadd_back(&head, new);
	}
	return (head);
}

void	built_ins_init_struct(t_com *commands)
{
	if (!ft_strncmp(commands->command, "echo", ft_strlen(commands->command))
		|| !ft_strncmp(commands->command, "pwd", ft_strlen(commands->command))
		|| !ft_strncmp(commands->command, "cd", ft_strlen(commands->command))
		|| !ft_strncmp(commands->command, "exit", ft_strlen(commands->command))
		|| !ft_strncmp(commands->command, "env", ft_strlen(commands->command))
		|| !ft_strncmp(commands->command, "export",
			ft_strlen(commands->command)) || !ft_strncmp(commands->command,
			"unset", ft_strlen(commands->command)))
		commands->flag_built = 1;
}

void	init_struct(char *line, char *cmd, int end, t_com *commands)
{
	if (!cmd || !line)
		return ;
	commands->command = ft_substr(cmd, 0, ft_strlen(cmd));
	while (line[end] == ' ')
		end++;
	if (has_expandable_dollar(line + end))
	{
		commands->args = ft_split_parser(line + end);
		redirects(commands);
		expand_args(commands);
	}
	else
	{
		keep_quotes_args(commands, line + end);
		redirects(commands);
		clean_reinserted_quotes_in_args(commands);
	}
	if (commands->command && ft_strlen(commands->command) > 0)
		built_ins_init_struct(commands);
	commands->command_arg = ft_strjoin_cmd_arg(commands);
}
