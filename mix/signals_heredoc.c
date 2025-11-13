/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:39:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/11 18:42:41 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "^C\n", 3);
}

void	setup_terminal_heredoc(void)
{
	struct termios	new_termios;
	struct termios	*original;
	int				*saved;

	original = get_original_termios();
	saved = get_termios_saved();
	if (tcgetattr(STDIN_FILENO, original) != 0)
		return ;
	*saved = 1;
	new_termios = *original;
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	setup_terminal_heredoc();
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
