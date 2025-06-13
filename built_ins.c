/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:57:17 by roo               #+#    #+#             */
/*   Updated: 2025/06/13 17:05:54 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_funtion(t_vars *vars)
{
	int		i;
	ssize_t bytes_written;
    
    i = 1;
	bytes_written = 0;
	while(vars->params[i] && bytes_written != -42)
	{
		bytes_written = write(vars->output_fd, vars->params[i], ft_strlen(vars->params[i]));
		if(vars->params[i + 1])
		bytes_written = write(vars->output_fd, " ", 1);
		i++;
	}
	bytes_written = write(vars->output_fd, "\n", 1);
}

/*void	pwd_funtion(t_vars *vars)
{
}*/
