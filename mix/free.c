/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:17:12 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:17:15 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s_vars
// {
// 	int		argc; //añadiendo argc y argv para tenerlos siempre a mano.
// 	char	**argv;
// 	char	**env;
// }	t_vars;

void free_t_vars_list(t_vars *list)
{
    if (list->argv)
        ft_free_free(list->argv);
    if (list->env)
        ft_free_free(list->env);
    free(list);
}

// typedef struct s_red
// {
// 	char	**input_file; //archivo para redirección con <
// 	char	**output_file; // archivo para redirección con >
// 	char	**append_file; //archivo para redirección con >>
// 	char	*delimiter; // palabra que delimita el heredoc <<
// 	int		redirect_in; // flag 1 si hay <, 0 si no hay
// 	int		redirect_out; // flag 1 si hay >, 0 si no hay
// 	int		redirect_append; // flag 1 si hay >>, 0 si no hay
// 	int		redirect_heredoc; // flag 1 si hay <<, 0 si no hay
// 	int		j; //posicion en char * de < ó >
// 	int		i; //posicion en char ** de < ó >
// 	int		sintax_error; //sintax error
// 	int		error; //falta a donde redireccionar
// }	t_red;

void free_t_red_list(t_red *list)
{
    if (list->input_file)
        ft_free_free(list->input_file);
    if (list->output_file)
        ft_free_free(list->output_file);
    if (list->append_file)
        ft_free_free(list->append_file);
    if (list->delimiter)
        free(list->delimiter);
}

// typedef struct s_com
// {
// 	struct s_com *previous;
// 	char *command; // ej: "ls"
// 	char *command_arg; // ej: "ls -la"
// 	char **args; // ej: "-la" ---> 
// 	char *path_command; // ej: "/usr/bin/ls"
// 	int fd_in; // cada comando tiene su propio input y output
// 	int fd_out; // cada comando tiene su propio input y output
// 	int index; //para saber en que nodo de la lista estas
// 	int i; // no guarda información util, es para ahorrar lineas, un iterador normal
// 	int flag_built; // 1 para built 0 execve
// 	int flag_pipe; // 1 si hay pipe 0 si no
// 	char *error;
// 	struct s_com *next;
// 	t_red *redirects; // estructura para > >> < <<
// 	t_vars *vars;
// }	t_com;

void free_t_com_list(t_com *list)
{
    if(list->command)
        free(list->command);
    if(list->command_arg)
        free(list->command_arg);
    if(list->args)
        ft_free_free(list->args);
    if(list->path_command)
        free(list->path_command);
    if (list->error)
        free(list->error);
    if(list->redirects)
        free_t_red_list(list->redirects);
    if (list->vars)
        free_t_vars_list(list->vars);
}       