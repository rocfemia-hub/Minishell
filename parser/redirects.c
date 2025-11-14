/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/14 00:00:00 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_redirects(t_com *commands, char *redirect, int type)
{
	char	*redirect_pos;
	char	*arg;

	if (!commands->args[commands->redirects->j])
		return (1);
	arg = commands->args[commands->redirects->j];
	if (ft_strlen(arg) == ft_strlen(redirect)
		&& ft_strncmp(arg, redirect, ft_strlen(redirect)) == 0)
		return (aux_parser_redirects(commands, redirect, type));
	else if (ft_strlen(arg) > ft_strlen(redirect))
	{
		redirect_pos = find_redirect_position(arg, redirect);
		if (redirect_pos)
			aux_redirects(commands, redirect_pos, type, redirect);
		else
			handle_no_redirect_pos(commands, redirect, type);
	}
	return (1);
}

int	process_redirect(t_com *commands, int first_idx)
{
	if (first_idx == 2 && !parser_redirects(commands, "<<", 4))
		return (0);
	else if (first_idx == 3 && !parser_redirects(commands, ">>", 3))
		return (0);
	else if (first_idx == 0 && !parser_redirects(commands, "<", 1))
		return (0);
	else if (first_idx == 1 && !parser_redirects(commands, ">", 2))
		return (0);
	return (1);
}

int	aux_find(t_com *commands, char **pos, char *first)
{
	int	first_idx;

	first_idx = find_first_redirect(pos, first);
	if (first_idx == -1)
		return (1);
	if (!process_redirect(commands, first_idx))
		return (0);
	commands->redirects->j--;
	return (1);
}

void	redirects(t_com *commands)
{
	char	*temp;

	commands->redirects = ft_calloc(1, sizeof(t_red));
	if (!commands->redirects)
		return ;
	if (is_redirect_token(commands->command, "<")
		|| is_redirect_token(commands->command, "<<")
		|| is_redirect_token(commands->command, ">")
		|| is_redirect_token(commands->command, ">>"))
	{
		if (!redirects_cmd(commands, commands->command))
			return ;
	}
	else
	{
		temp = clean_quotes_in_line(commands->command);
		commands->command = ft_strdup(temp);
		free(temp);
	}
	find(commands);
}
