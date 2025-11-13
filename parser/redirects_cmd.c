/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:59:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	clean_redirects_cmd(t_com *commands, char *redirect, int type)
{
	if (ft_strnstr(commands->command, ">>>", 3))
	{
		commands->error = ft_strdup("near unexpected token `>'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strnstr(commands->command, "<<<", 3))
	{
		commands->error = ft_strdup("near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else
		aux_clean_redirects_cmd(commands, redirect, type);
	return (1);
}

int	aux_redirects_cmd(t_com *commands)
{
	if (commands->args[0] || ft_strlen(commands->command) > 2)
	{
		if (is_redirect_token(commands->command, "<<"))
			if (!clean_redirects_cmd(commands, "<<", 4))
				return (0);
		if (is_redirect_token(commands->command, ">>"))
			if (!clean_redirects_cmd(commands, ">>", 3))
				return (0);
		look_for_cmd(commands);
		return (1);
	}
	else
	{
		commands->error = ft_strdup("near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
}

static int	handle_single_redirects(t_com *commands)
{
	if (commands->args[0] || ft_strlen(commands->command) > 1)
	{
		if (is_redirect_token(commands->command, "<"))
			clean_redirects_cmd(commands, "<", 1);
		if (is_redirect_token(commands->command, ">"))
			clean_redirects_cmd(commands, ">", 2);
		look_for_cmd(commands);
		return (1);
	}
	else
	{
		commands->error = ft_strdup("near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
}

int	redirects_cmd(t_com *commands)
{
	if (is_redirect_token(commands->command, "<<")
		|| is_redirect_token(commands->command, ">>"))
	{
		if (!aux_redirects_cmd(commands))
			return (0);
	}
	if (is_redirect_token(commands->command, "<")
		|| is_redirect_token(commands->command, ">"))
		return (handle_single_redirects(commands));
	return (0);
}
