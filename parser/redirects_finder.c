/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_finder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:00:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/17 18:17:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_no_redirect_pos(t_com *commands, char *redirect, int type)
{
	char	*tmp_file;

	tmp_file = ft_strdup(commands->args[commands->redirects->j]
			+ ft_strlen(redirect));
	fill_type_redirect(commands, type);
	commands->args = copy_redirect_matrix(commands->args,
			commands->redirects->j, commands->redirects->j);
	fill_red(commands, redirect, tmp_file);
}

int	find_first_redirect(char **pos, char *first)
{
	int	i;
	int	first_idx;

	first_idx = -1;
	i = -1;
	while (++i < 4)
	{
		if (pos[i] && (!first || pos[i] < first || (pos[i] == first
					&& i > first_idx)))
		{
			first = pos[i];
			first_idx = i;
		}
	}
	return (first_idx);
}

void	init_redirect_positions(t_com *commands, char **pos)
{
	char	*arg;

	arg = commands->args[commands->redirects->j];
	pos[0] = find_redirect_position(arg, "<");
	pos[1] = find_redirect_position(arg, ">");
	pos[2] = find_redirect_position(arg, "<<");
	pos[3] = find_redirect_position(arg, ">>");
}

void	find(t_com *cmds)
{
	char	*pos[4];
	char	*first;
	char	**temp;

	first = NULL;
	if (!cmds->args || !cmds->redirects)
		return ;
	while (cmds->args[cmds->redirects->j])
	{
		init_redirect_positions(cmds, pos);
		if (!aux_find(cmds, pos, first))
			return ;
		cmds->redirects->j++;
	}
	if (ft_strlen(cmds->command) == 0 && cmds->args && cmds->args[0])
	{
		if (cmds->command)
			free(cmds->command);
		cmds->command = clean_quotes_in_line(ft_strdup(cmds->args[0]),
				&cmds->quoted);
		temp = redirect_args(cmds);
		free(cmds->args[0]);
		free(cmds->args);
		cmds->args = temp;
	}
}

char	*find_redirect_position(char *arg, char *redirect)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (quote == 0)
				quote = arg[i];
			else if (quote == arg[i])
				quote = 0;
		}
		else if (!quote && ft_strncmp(arg + i, redirect,
				ft_strlen(redirect)) == 0)
			return (arg + i);
		i++;
	}
	return (NULL);
}
