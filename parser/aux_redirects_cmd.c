/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:59:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**realloc_redirect_args(char **flag)
{
	int		i;
	int		j;
	char	**realloc_matrix;

	j = 0;
	while (flag[j])
		j++;
	realloc_matrix = ft_calloc(j, sizeof(char *));
	if (!realloc_matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (flag[++i])
	{
		realloc_matrix[j] = ft_strdup(flag[i]);
		j++;
	}
	ft_free_free(flag);
	return (realloc_matrix);
}

void	look_for_cmd(t_com *commands)
{
	char	**temp;
	int		i;

	i = 0;
	if (!commands || !commands->args)
		return ;
	while (commands->args[i])
	{
		if (is_redirect_token(commands->args[i], "<<") || is_redirect_token(commands->args[i], ">>") || is_redirect_token(commands->args[i], "<") || is_redirect_token(commands->args[i], ">"))
			find(commands);
		i++;
	}
	if (!commands->command || ft_strlen(commands->command) < 1)
	{
		if (commands->args[0])
		{
			if (commands->command)
				free(commands->command);
			commands->command = ft_strdup(commands->args[0]);
			temp = realloc_redirect_args(commands->args);
			commands->args = temp;
		}
	}
}
