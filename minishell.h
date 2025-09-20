/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/09/16 18:56:10 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ_FD 0
# define WRITE_FD 1

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>

typedef struct s_clean_cmd
{
	int		i;
    int		start;
    int		end;
    char	quote;
    char	*cmd;
	int		end_index;
} t_clean_cmd;

typedef struct s_vars
{
	int		argc; //añadiendo argc y argv para tenerlos siempre a mano.
	char	**argv;
	char	**env;
}	t_vars;

typedef struct s_red
{
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
	int		sintax_error; //sintax error
	int		error; //falta a donde redireccionar
}	t_red;

typedef struct s_com
{
	struct s_com *previous;
	char *command; // ej: "ls"
	char *command_arg; // ej: "ls -la"
	char **args; // ej: "-la" ---> 
	char *path_command; // ej: "/usr/bin/ls"
	int fd_in; // cada comando tiene su propio input y output
	int fd_out; // cada comando tiene su propio input y output
	int index; //para saber en que nodo de la lista estas
	int i; // no guarda información util, es para ahorrar lineas, un iterador normal
	int flag_built; // 1 para built 0 execve
	int flag_pipe; // 1 si hay pipe 0 si no
	char *error;
	struct s_com *next;
	t_red *redirects; // estructura para > >> < <<
	t_vars *vars;
}	t_com;


/*MIX*/ 


// MAIN
int		line_break(char *line);
void	init_vars(t_vars *vars, int argc, char **argv,  char **env);
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


/*EXEC*/ 


// EXECUTOR
void	setup_pipeline(t_com *list);
void	execute_control(t_com *list, t_vars *vars);
void	commands_control(t_com *list, t_vars *vars);
char	*get_path(char *cmd, char **envp, t_com *pipex);
int		execute(t_com *list);
void	execute_two(t_com *list, int fd[2]);

// BUILT-INS
void	echo_function(t_com *list, t_vars *vars);
void	pwd_function(t_com *list, t_vars *vars);
void	exit_function(t_com *list, t_vars *vars);
void	cd_function(t_com *list, t_vars *vars);

void	env_function(t_com *list, t_vars *vars);
void	export_function(t_com *list, t_vars *vars);
void	unset_function(t_com *list, t_vars *vars);

// UTILS_BUILT-INS
int		valid_n_option(char *str);
int		valid_number(char *str);
void	print_export_vars(t_com *list, t_vars *vars);
void	remove_env_var(char **env, int index);

void	add_env_var(char *new_var, t_vars *vars);
void	add_new_env_vars(char *new_var, t_vars *vars);
int		find_env_var(char *var_name, t_vars *vars);
char	*get_var_name(char *var_assignment);
void	export_existing_var(char *var_name, t_vars *vars);

// REDIRECTIONS
void set_redirections(t_com *list);
void heredoc_execution(t_com *list);
void clean_fds(t_com *list);


/*PARSER*/ 


// TOKEN.C
void	type_command(char *line, t_com *commands);
void	init_commands(char *line, t_com *commands);
t_com	*token(char *line);

// SPLIT_MINI.C
char	**ft_split_mini(char const *s, char c);

// QUOTES
void 	*clean_arg(t_com *commands, char *line);
char	*clean_cmd(char *line, t_clean_cmd *data);
int		pipes_counter(char *line);

// TRUCT
char 	*ft_strjoin_mini(t_com *commands);
t_com	*create_struct(char *line);
void	init_struct(char *line, char *cmd, int end, t_com *commands);
void 	clean_and_fill_arg(t_com *commands, char *line);

// EXPANDER_CMD
void expand_cmd(t_clean_cmd *data);
char **aux_cmd(t_clean_cmd *data);
char *only_cmd(char *line, t_clean_cmd *data);
char *ft_strjoin_cmd(char **cmd);

// EXPANDER_ARGS
char *get_env_var(const char *var);
char *str_append(char *dest, const char *src);
char *expand_args(char *line);
char **aux_args(char *line);


// REDIRECTS
char **copy_matrix(char **args);
char **realloc_redirect_flags(char **flag);
void fill(t_com *commands, int start, int end, char *redirect, char *file);
int parser_redirects(t_com *commands, char *redirect);
void find(t_com *commands);
void redirects(t_com *commands);


#endif