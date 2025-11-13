/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:49:46 by roo               #+#    #+#             */
/*   Updated: 2025/11/12 22:51:08 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_var(t_com *list, t_env *env)
{
	char	*line;

	line = ft_strjoin(env->env_name, "=");
	if (env->env_inf)
		line = ft_strjoin_gnl(line, env->env_inf);
	write(list->fd_out, line, ft_strlen(line));
	write(list->fd_out, "\n", 1);
	free(line);
}
