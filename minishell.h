/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/06/13 17:05:59 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Helicopter/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct vars
{
	char **params;
	int     output_fd;
    int     input_fd;
	int     exit_status;
} t_vars;

//MAIN

void	commands_control(t_vars *vars);

//BUILT-INS

void	echo_funtion(t_vars *vars);
//void	pwd_funtion(t_vars *vars);

#endif