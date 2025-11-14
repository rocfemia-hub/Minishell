/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/14 00:00:00 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

static int	handle_single_redirects(t_com *commands)
{
	if (commands->args[0] || ft_strlen(commands->command) > 1)
	{
		while (commands->command && is_redirect(commands->command[0]))
		{
			if (commands->command[0] == '<' && commands->command[1] == '<')
				clean_redirects_cmd(commands, "<<", 4);
			else if (commands->command[0] == '>' && commands->command[1] == '>')
				clean_redirects_cmd(commands, ">>", 3);
			else if (commands->command[0] == '<')
				clean_redirects_cmd(commands, "<", 1);
			else if (commands->command[0] == '>')
				clean_redirects_cmd(commands, ">", 2);
			if (!commands->command)
				break ;
		}
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

int	redirects_cmd(t_com *commands, char *cmd)
{
	if (is_redirect_token(cmd, "<<") || is_redirect_token(cmd, ">>")
		|| is_redirect_token(cmd, "<") || is_redirect_token(cmd, ">"))
		return (handle_single_redirects(commands));
	return (0);
}
