/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:39:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 17:54:23 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Handler para heredoc - SIGINT debe salir del heredoc
void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	// Escribir ^C manualmente y nueva línea
	write(STDOUT_FILENO, "^C\n", 3);
}

// Configurar terminal para heredoc - desactivar eco de caracteres de control
void	setup_terminal_heredoc(void)
{
	struct termios	new_termios;
	struct termios	*original;
	int				*saved;

	original = get_original_termios();
	saved = get_termios_saved();
	// Guardar configuración original del terminal
	if (tcgetattr(STDIN_FILENO, original) != 0)
		return ;
	*saved = 1;
	// Copiar configuración original y modificar
	new_termios = *original;
	// Desactivar SIGQUIT (Ctrl+\) para que no genere señal
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	// Desactivar el eco de caracteres de control (^C, ^\, etc.)
	new_termios.c_lflag &= ~ECHOCTL;
	// Aplicar nueva configuración
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// Configurar señales para heredoc
void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	// Configurar terminal para no mostrar caracteres de control
	setup_terminal_heredoc();
	// Configurar SIGINT para que interrumpa read() inmediatamente
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; // Sin flags especiales, comportamiento estándar
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
