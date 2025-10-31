/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:39:55 by roo               #+#    #+#             */
/*   Updated: 2025/10/30 00:00:00 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Handler para SIGINT en modo interactivo (main shell)
void handle_sigint_interactive(int sig)
{
    (void)sig;
    g_signal = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

// Handler para SIGINT en procesos hijos
void handle_sigint_child(int sig)
{
    (void)sig;
    g_signal = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
}

// Handler para heredoc - SIGINT debe salir del heredoc
void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;

	// Escribir ^C manualmente y nueva línea
	write(STDOUT_FILENO, "^C\n", 3);
}

// Variables estáticas para guardar configuración del terminal
static struct termios	*get_original_termios(void)
{
	static struct termios original_termios;
	return (&original_termios);
}

static int	*get_termios_saved(void)
{
	static int termios_saved = 0;
	return (&termios_saved);
}

// Configurar terminal para heredoc - desactivar eco de caracteres de control
void	setup_terminal_heredoc(void)
{
	struct termios	new_termios;

	// Guardar configuración original del terminal
	if (tcgetattr(STDIN_FILENO, get_original_termios()) != 0)
		return;
	*get_termios_saved() = 1;

	// Copiar configuración original y modificar
	new_termios = *get_original_termios();
	
	// Desactivar SIGQUIT (Ctrl+\) para que no genere señal
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	
	// Desactivar el eco de caracteres de control (^C, ^\, etc.)
	new_termios.c_lflag &= ~ECHOCTL;

	// Aplicar nueva configuración
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// Restaurar configuración original del terminal
void	restore_terminal_heredoc(void)
{
	if (*get_termios_saved())
	{
		tcsetattr(STDIN_FILENO, TCSANOW, get_original_termios());
		*get_termios_saved() = 0;
	}
}// Configurar señales para modo interactivo (main shell)
void setup_signals_interactive(void)
{
    signal(SIGINT, handle_sigint_interactive);
    signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT en modo interactivo
}

// Configurar señales para ejecución de comandos
void setup_signals_noninteractive(void)
{
    signal(SIGINT, handle_sigint_child);
    signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT en comandos también
}

// Configurar señales para heredoc
void setup_signals_heredoc(void)
{
    struct sigaction sa;
    
    // Configurar terminal para no mostrar caracteres de control
    setup_terminal_heredoc();
    
    // Configurar SIGINT para que interrumpa read() inmediatamente
    sa.sa_handler = handle_sigint_heredoc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // Sin flags especiales, comportamiento estándar
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}

// Configurar señales por defecto para procesos hijos
void setup_signals_default(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT también en procesos hijos
}