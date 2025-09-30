/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:39:55 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:39:56 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_c()
{
	rl_on_new_line(); //limpia la linea
	write(1, "\r\n", 2); // escribe salto de linea
	rl_on_new_line(); // limpia la linea
	rl_redisplay(); // me escribe minishell ->
}

void handle_backslash(int sig)
{
    (void)sig; // la casteo para hacer algo con ella y que no me de error al compilar 
    write(1, "\n", 1);
}