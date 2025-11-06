/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/06 18:17:18 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# define READ_FD 0
# define WRITE_FD 1

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_clean_cmd
{
	int		i;
    int		start;
    int		end;
    char	quote;
    char	*cmd;
	int		end_index;
	int		only_cmd_i;
} t_clean_cmd;

typedef struct s_env
{
	char	*env_name;
	char	*env_inf;
	struct s_env *next;
}	t_env;

typedef struct s_vars
{
	char	*pwd;
	t_env	*env_list; // para cambios de variables, es más facil gestionar liberación de memoria con una lista que con una matriz
	int		exit_status;
}	t_vars;

typedef struct s_red
{
	int		redirected; //flag para ver si ya he redireccionado
	int		*t_red; //array d int para saber cual es ek orden en el q lo escriben por terminal (1-input, 2-output, 3-append, 4-heredoc)
	char	**input_file; //archivo para redirección con <
	char	**output_file; // archivo para redirección con >
	char	**append_file; //archivo para redirección con >>
	char	*delimiter; // palabra que delimita el heredoc <<
	char	*heredoc_file; // NUEVO: archivo oculto para el heredoc <<
	int		redirect_in; // flag 1 si hay <, 0 si no hay
	int		redirect_out; // flag 1 si hay >, 0 si no hay
	int		redirect_append; // flag 1 si hay >>, 0 si no hay
	int		redirect_heredoc; // flag 1 si hay <<, 0 si no hay
	int		j; //posicion en char * de < ó >
	int		i; //posicion en char ** de < ó >
	int		err;
	int		sintax_error; //sintax error
	int		error; //falta a donde redireccionar
}	t_red;

typedef struct s_com
{
	struct s_com *previous;
	char *command; // ej: "ls"
	char **command_arg; // ej: "ls -la"
	char **args; // ej: "-la" ---> 
	char *path_command; // ej: "/usr/bin/ls"
	int fd_in; // cada comando tiene su propio input y output
	int fd_out; // cada comando tiene su propio input y output
	int index; //para saber en que nodo de la lista estas
	int i; // no guarda información util, es para ahorrar lineas, un iterador normal
	int flag_built; // 1 para built 0 execve
	int flag_pipe; // 1 si hay pipe 0 si no
	char *error;
	int n_args; //se utiliza en keep_quotes_args en quotes.c
	int expanded; // 1 si ya se expandieron los args, 0 si no
	struct s_com *next;
	t_red *redirects; // estructura para > >> < <<
	t_vars *vars;
}	t_com;


/*MIX*/ 


// MAIN
void 	init_env(t_vars *vars);
int		line_break(char *line);
int		matrix_len(char **matrix);
char	**malloc_matrix(char **matrix); // NO SE USA
void	init_vars(t_vars *vars, char **env);
void	init_fds(t_com *list, t_vars *vars);

//LISTAS
t_com	*lstnew(int index);
void	lstadd_back(t_com **lst, t_com *new);
void 	print_list(t_com *list);

//ERROR
void	printf_matrix(char **split);
void 	error(t_com *commands);

//FREE
void	free_t_com_list(t_com *list);
void	free_t_red_list(t_red *list);
void	free_t_vars_list(t_vars *list);

// SPLIT_MINI.C
char	**ft_split_mini(char const *s, char c);
void	free_array(char **p);

//SIGNALS
extern int g_signal;

void	handle_sigint_interactive(int sig);
void	handle_sigint_child(int sig);
void	handle_sigquit_child(int sig);
void	handle_sigint_heredoc(int sig);
void	setup_signals_interactive(void);
void	setup_signals_noninteractive(void);
void	setup_signals_heredoc(void);
void	setup_signals_default(void);
void	setup_terminal_heredoc(void);
void	rest_termi_hrdc(void);

/*EXEC*/ 


// EXECUTOR
void	execute_control(t_com *list, t_vars *vars);
void	commands_control(t_com *list, t_vars *vars);
char	*get_path(char *cmd, t_vars *vars);
int 	execute(t_com *list, t_vars *vars);
int		execute_error_control(t_com *list);
int		pids_funcion(t_com *list, int status);
void	execute_signals(t_com *list, int status);

// PIPELINES
void	setup_pipeline(t_com *list);
void	execute_pipeline(t_com *list);
void	execute_pipelines2(t_com *list, pid_t *pids);
void	pipelines_signals(t_com *list, pid_t *pids, int num_cmds, int i);
void	pids_pipelines(t_com *list, t_com *tmp_list, pid_t *pids, int i);
void	pids2_pipelines(t_com *list, t_com *tmp_list);
void	close_pipes(t_com *list, t_com *current_cmd);

// BUILT-INS
void	echo_function(t_com *list, t_vars *vars);
void	pwd_function(t_com *list, t_vars *vars);
void	exit_function(t_com *list, t_vars *vars);
void	cd_function(t_com *list, t_vars *vars, char *target_dir);

void	env_function(t_com *list, t_vars *vars);
void	export_function(t_com *list, t_vars *vars);
void	unset_function(t_com *list, t_vars *vars);

// UTILS_BUILT-INS
int		valid_n_option(char *str);
int		valid_number(char *str);
void	print_export_vars(t_com *list, t_vars *vars);
void	remove_env_var(t_vars *vars, char *name);
int		cd_aux_funcion(t_com *list, t_vars *vars);

void	add_update_env_var(t_vars *vars, char *var_str);
char	*get_var_name(char *var_assignment); // NO SE USA
int		valid_var_name(char *var);

char	**list_to_env(t_env *env_list);
void	env_to_list(t_vars *vars, char **env);
t_env	*create_env_list(char *env_string);
void	add_env_var_to_list(t_vars *vars, char *name, char *value);
t_env	*find_env_var(t_vars *vars, char *env_name);

// REDIRECTIONS
int		redirections_control(t_com *list, int j, int q, int k);
int		infile_redirection(t_com *list, int i);
int		outfile_redirection(t_com *list, int i);
int		append_redirection(t_com *list, int i);
void	heredoc_execution(t_com *list);
void	found_delimiter(t_com *list, int fd);
void	apply_redirections(t_com *list);
void	clean_fds(t_com *list);


/*PARSER*/ 


// TOKEN.C
int		skip_spaces(char *line);
char	*only_cmd(char *line, t_clean_cmd *data);
void	type_command(char *line, t_com *commands);
void	init_commands(char *line, t_com *commands);
t_com	*token(char *line, t_vars *vars);

// SYNTAX_VALIDATOR.C
int		validate_syntax(char *line);

// FT_SPLIT_PARSER.C
int		skip_space(char *s, int i);
int		count_words_with_quotes(char *s);
char	*extract_token(char *s, int *i);
char	**ft_split_parser(char const *s);

// QUOTES.C
void	keep_quotes_args(t_com *commands, char *line);
void	clean_reinserted_quotes_in_args(t_com *commands);
char	*clean_cmd(char *line);
int		look_for_char(char *line, char c);

// STRUCT.C
char	**ft_strjoin_cmd_arg(t_com *commands);
int		has_expandable_dollar(char *line);
t_com	*create_struct(char *line, t_vars *vars);
void	init_struct(char *line, char *cmd, int end, t_com *commands);

// EXPANDER_CMD.C
char	*str_append(char *dest, const char *src);
char	*handle_plain_text(char *cmd, int *i, t_vars *vars);
char	*aux_cmd(t_clean_cmd *data, t_vars *vars);
int		expand_cmd(t_clean_cmd *data, t_vars *vars);

// EXPANDER_ARGS.C
char	*ft_strjoin_cmd(char **cmd);
char	*handle_plain_text_args(char *line, int *i, t_vars *vars);
char	*process_single_arg(char *arg, t_vars *vars);
char	**process_aux_args(char **args, char **token_args, t_vars *vars);
void	expand_args(t_com *commands);

// UTILS_EXPANDER.C
char	*handle_single_quotes(char *line, int *i, t_vars *vars);
char	*aux_expand_var_in_quotes_args(char *token, t_vars *vars, int *k, int *start);
char	*expand_var_in_quotes_args(char *line, int *k, int *start, char *token, t_vars *vars);
char	*process_inside_double_quotes(char *line, int start, int end, t_vars *vars);
char	*handle_double_quotes(char *line, int *i, t_vars *vars);

// AUX_EXPANDER.C
char	*handle_inter(t_vars *vars);
char	*get_env_var(t_vars *vars, char *var);
char	*extract_varname(char *line, int start, int *vlen);
char	*aux_handle_dollar(int *i, int start);
char	*handle_dollar(char *line, int *i, t_vars *vars);

// REDIRECTS.C
int		aux_parser_redirects(t_com *commands, char *redirect, int type);
char	*find_redirect_position(char *arg, char *redirect);
int		aux_parser_resdirects_sintax_error(t_com *commands);
void	aux_redirects(t_com *commands, char *redirect_pos, int type, char *redirect);
int		parser_redirects(t_com *commands, char *redirect, int type);
char	*clean_quotes_in_line(char *arg);
int		is_redirect_token(char *arg, char *redirect);
void	find(t_com *commands);
void	redirects(t_com *commands);

// UTILS_REDIRECTS.C
char	**realloc_redirect_flags(char **flag);
char	**copy_redirect_matrix(char **args, int start, int end);
char	*expand_redirect_filename(char *file, t_vars *vars);
void	handle_redirect_array(char ***arr, int *flag, char *file, t_com *commands);
void	fill_type_redirect(t_com *commands, int type);

// REDIRECTS_CMD.C
char	**realloc_redirect_args(char **flag);
void	look_for_cmd(t_com *commands);
void	fill_cmd(t_com *commands, char *redirect, char *file);
void	aux_clean_redirects_cmd(t_com *commands, char *redirect, int type);
int		clean_redirects_cmd(t_com *commands, char *redirect, int type);
int		aux_redirects_cmd(t_com *commands);
int		redirects_cmd(t_com *commands);

#endif