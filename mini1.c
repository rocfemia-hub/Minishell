/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:56:08 by roo               #+#    #+#             */
/*   Updated: 2025/06/13 17:06:07 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	t_vars	*vars;
	char	*line;
	
	vars = ft_calloc(1, sizeof(t_vars));
	vars->output_fd = 1;
    vars->input_fd = 0;
    vars->exit_status = 0;
	if (!argc && argv)
		return 1;
	while(1)
	{
		line = readline("minishell> ");
		if(!line)
			break;
		vars->params = ft_split(line, ' ');
		if(vars->params[0] && ft_strncmp(vars->params[0], "exit", 5) == 0)
			break;
		commands_control(vars);
		ft_free_free(vars->params);
		free(line);
	}
}

void commands_control(t_vars *vars)
{
	if(vars->params[0] && ft_strncmp(vars->params[0], "echo", 5) == 0)
    	echo_funtion(vars);
	/*if(vars->params[0] && ft_strncmp(vars->params[0], "pwd", 4) == 0)
		pwd_funtion(vars);*/
}
