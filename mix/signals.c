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

void handle_c(int sig)
{
    (void)sig;
    rl_on_new_line();
    write(1, "\n", 1);
    rl_replace_line("", 0); // limpia la línea que se estaba escribiendo
    rl_redisplay();
}

void handle_backslash(int sig)
{
    (void)sig; // la casteo para hacer algo con ella y que no me de error al compilar 
    write(1, "\n", 1);
}