/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 21:51:56 by roo              ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_clean_cmd
{
	int				i;
	int				start;
	int				end;
	char			quote;
	char			*cmd;
	int				only_cmd_i;
}					t_clean_cmd;

typedef struct s_env
{
	char			*env_name;
	char			*env_inf;
	int				hidden;
	struct s_env	*next;
}					t_env;

typedef struct s_vars
{
	char			*pwd;
	t_env			*env_list;
	int				exit_status;
}					t_vars;

typedef struct s_red
{
	int				*t_red;
	char			**input_file;
	char			**output_file;
	char			**append_file;
	char			*delimiter;
	char			*heredoc_file;
	int				redirect_in;
	int				redirect_out;
	int				redirect_append;
	int				redirect_heredoc;
	int				j;
}					t_red;

typedef struct s_com
{
	struct s_com	*previous;
	char			*command;
	char			**command_arg;
	char			**args;
	char			*path_command;
	int				fd_in;
	int				fd_out;
	int				index;
	int				flag_built;
	int				flag_pipe;
	char			*error;
	int				expanded;
	struct s_com	*next;
	t_red			*redirects;
	t_vars			*vars;
	int				quoted;
}					t_com;

/*MIX*/

// MAIN

// LISTAS
t_com				*lstnew(int index);
void				lstadd_back(t_com **lst, t_com *new);

// ERROR
void				error(t_com *commands);

// FREE
void				free_t_com_list(t_com *list);

// SPLIT_MINI.C
char				**ft_split_mini(char const *s, char c);
void				free_array(char **p);

// SIGNALS
extern int			g_signal;

void				handle_sigint_interactive(int sig);
struct termios		*get_original_termios(void);
int					*get_termios_saved(void);
void				rest_termi_hrdc(void);
void				setup_signals_interactive(void);

// SIGNALS_CHILD.C
void				aux_pipe_signal(t_com *list, int status, int i,
						int num_cmds);
void				pipelines_signals(t_com *list, pid_t *pids, int num_cmds,
						int i);
void				setup_signals_default(void);
void				setup_signals_noninteractive(void);

// SIGNALS_HEREDOC.C
void				handle_sigint_heredoc(int sig);
void				setup_terminal_heredoc(void);
void				setup_signals_heredoc(void);

/*EXEC*/

// BUILT-INS
void				echo_function(t_com *list, t_vars *vars);
void				pwd_function(t_com *list, t_vars *vars);
void				exit_function(t_com *list, t_vars *vars);
void				cd_function(t_com *list, t_vars *vars, char *target_dir);

void				env_function(t_com *list, t_vars *vars);
void				export_function(t_com *list, t_vars *vars);
void				unset_function(t_com *list, t_vars *vars);

// UTILS_BUILT-INS
int					valid_n_option(char *str);
int					valid_number(char *str);
int					valid_var_name(char *var);
int					cd_aux_funcion(t_com *list, t_vars *vars);
void				print_export_vars(t_com *list, t_vars *vars);
int					is_variable_assignment(char *cmd);

t_env				*create_env_list(char *env_string);
t_env				*find_env_var(t_vars *vars, char *env_name);
void				add_update_env_var(t_vars *vars, char *var_str, int hidden);
void				remove_env_var(t_vars *vars, char *name);
int					export_var(t_vars *vars, char *var, int hidden);

char				**list_to_env(t_env *env_list);
void				env_to_list(t_vars *vars, char **env);
void				increment_shlvl(t_vars *vars);
int					line_break(char *line);

int					number_in_range(char *str);
void				print_env_var(t_com *list, t_env *env);

// EXEC_CONTROL
void				execute_control(t_com *list, t_vars *vars);
void				commands_control(t_com *list, t_vars *vars);
int					redirections_control(t_com *list, int j, int q, int k);

// EXECUTOR
char				*get_path(char *cmd, t_vars *vars);
int					execute(t_com *list, t_vars *vars);
void				execute_signals(t_com *list, int status);

// HERERDOC
void				heredoc_execution(t_com *list);

// PIDS
int					pids_funcion(t_com *list, int status);
void				pids_pipelines(t_com *list, t_com *tmp_list, pid_t *pids,
						int i);

// PIPELINES
void				execute_pipeline(t_com *list);
void				setup_pipeline(t_com *list);
void				close_pipes(t_com *list, t_com *current_cmd);

// REDIRECTIONS
int					infile_redirection(t_com *list, int i);
int					outfile_redirection(t_com *list, int i);
int					append_redirection(t_com *list, int i);
void				apply_redirections(t_com *list);

/*PARSER*/

// AUX_EXPANDER.C
char				*aux_handle_dollar(int *i, int start);
char				*handle_dollar(char *line, int *i, t_vars *vars);
char				*extract_and_expand_var(char *line, int vstart, int *vlen,
						t_vars *vars);
void				add_split_args(char **token_args, int *j,
						char *accumulated);

// AUX_REDIRECTS.C
int					aux_parser_redirects(t_com *commands, char *redirect,
						int type);
int					is_redirect_token(char *arg, char *redirect);
char				*extract_until_redirect(char *str, char **rest);
void				redirects_aux(t_com *commands, char *rest);
void				aux_redirects(t_com *commands, char *redirect_pos, int type,
						char *redirect);

// AUX_TOKEN.C
int					skip_spaces(char *line);
void				aux_only_cmd(char *line, t_clean_cmd *data, int *quoted);
void				handle_quote(char c, char *quote);
void				process_quote_char(char current_char, char *new_arg, int *k,
						char *quote);
char				*clean_quotes_in_line(char *arg, int *quoted);

// EXPANDER_ARGS.C
char				*handle_plain_text_args(char *line, int *i, t_vars *vars);
char				*process_single_arg(char *arg, t_vars *vars);
char				**process_aux_args(char **args, char **token_args,
						t_vars *vars);
void				expand_args(t_com *commands);

// EXPANDER_CMD.C
char				*handle_dollar_in_quotes(char *line, int *k, int *start,
						t_vars *vars);
char				*str_append(char *dest, const char *src);
char				*handle_plain_text(char *cmd, int *i, t_vars *vars);
char				*aux_cmd(t_clean_cmd *data, t_vars *vars);
int					expand_cmd(t_clean_cmd *data, t_vars *vars,
						t_com *commands);

// EXPANDER.C
char				*handle_inter(t_vars *vars);
char				*get_env_var(t_vars *vars, char *var);
char				*handle_single_quotes(char *line, int *i, t_vars *vars);
char				*aux_expand_var_in_quotes_args(char *token, t_vars *vars,
						int *k, int *start);
char				*handle_invalid_var(char *token);

// FT_SPLIT_PARSER.C
int					skip_space(char *s, int i);
void				count_words_with_quotes(char *s, int i, int *words);
char				*extract_token(char *s, int *i);
char				**ft_split_parser(char const *s);

// KEEP_QUOTES.C
void				process_single_word(char *line, int *i, char **args,
						int *j);
void				aux_keep_quotes_args(char *line, int *i, int *k,
						char **arg);
void				keep_quotes_args(t_com *commands, char *line);

// QUOTES.C
void				clean_reinserted_quotes_in_args(t_com *commands);
char				*clean_cmd(char *line);

// REDIRECTS_CMD.C
int					is_char_protect(char c);
void				fill_red(t_com *commands, char *redirect, char *file);
char				**realloc_redirect_args(char **flag);
char				**redirect_args(t_com *commands);
int					is_redirect(char c);

// REDIRECTS.C
int					parser_redirects(t_com *commands, char *redirect, int type);
int					process_redirect(t_com *commands, int first_idx);
int					aux_find(t_com *commands, char **pos, char *first);
void				redirects(t_com *commands);

// STRUCT.C
t_com				*create_error_struct(int i, t_vars *vars);
t_com				*create_struct(char *line, t_vars *vars);
void				built_ins_init_struct(t_com *commands);
void				init_struct(char *line, char *cmd, int end,
						t_com *commands);

// SYNTAX_VALIDATOR.C
int					check_pipe_syntax(char *line, int i, char quote);
int					validate_syntax(char *line);

// TOKEN.C
char				*only_cmd(char *line, t_clean_cmd *data, int *quoted);
void				type_command(char *line, t_com *commands);
void				init_commands(char *line, t_com *commands);
t_com				*token(char *line, t_vars *vars);

// UTILS_EXPANDER.C
char				*extract_varname(char *line, int start, int *vlen);
char				*expand_var_in_quotes_args(char *line, int *k, char *token,
						t_vars *vars);
char				*process_inside_double_quotes(char *line, int start,
						int end, t_vars *vars);
char				*handle_double_quotes(char *line, int *i, t_vars *vars);

// UTILS_QUOTES.C
int					look_for_char(char *line, char c);
char				**ft_strjoin_cmd_arg(t_com *commands);
void				quotes_for_redir(char **arg, int *k, int start, char q);

// UTILS_REDIRECTS.C
char				**copy_redirect_matrix(char **args, int start, int end);
void				handle_redirect_array(char ***arr, int *flag, char *file,
						t_com *commands);
void				fill_type_redirect(t_com *commands, int type);

// REDIRECTS_FINDER.C
void				handle_no_redirect_pos(t_com *commands, char *redirect,
						int type);
int					find_first_redirect(char **pos, char *first);
void				init_redirect_positions(t_com *commands, char **pos);
void				find(t_com *commands);
char				*find_redirect_position(char *arg, char *redirect);

// UTILS_TILDE.C
char				*handle_tilde(char *cmd, int *i, t_vars *vars);

#endif