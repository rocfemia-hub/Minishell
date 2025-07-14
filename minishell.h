/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/07/01 20:03:43 by roo              ###   ########.fr       */
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


typedef struct s_pipes
{
	int pipes;
} t_pipes;

typedef struct s_vars
{
	int argc; //añadiendo argc y argv para tenerlos siempre a mano.
	char **argv;
	char **env;
} t_vars;

typedef struct s_com
{
	struct s_com *previous;
	char *command; // ej: "ls"
	char *command_arg; // ej: "ls -la"
	char *arg; // ej: "-la"
	char *path_command; // ej: "/usr/bin/ls"
	int fd_in; // cada comando tiene su propio input y output
	int fd_out; // cada comando tiene su propio input y output
	int index; //para saber en que nodo de la lista estas
	int i; // no guarda información util, es para ahorrar lineas, un iterador normal
	int flag_built; // 1 para built 0 execve
	struct s_com *next;
	t_vars *vars;
}	t_com;


/*MIX*/ 


// MAIN
void commands_control(t_com *list, t_vars *vars);
int line_break(char *line);
void init_vars(t_vars *vars, int argc, char **argv,  char **env);

//LISTAS
t_com *lstnew(int index);
void	lstadd_back(t_com **lst, t_com *new);
void 	print_list(t_com *list);
void	free_list(t_com *list);

//ERROR
void	printf_matrix(char **split);


/*EXEC*/ 


// BUILT-INS
void	echo_function(t_com *list, t_vars *vars);
void	pwd_function(t_com *list, t_vars *vars);
void	exit_function(t_com *list, t_vars *vars);
void	env_function(t_com *list, t_vars *vars);
void	cd_function(t_com *list, t_vars *vars);


// UTILS_BUILT-INS
int		valid_n_option(char *str);
int		valid_number(char *str);


/*PARSER*/ 


// TOKEN.C
void type_command(char *line, t_com *commands);
void init_commands(char *line, t_com *commands);
t_com *token(char *line);


// SPLIT_MINI.C
char	**ft_split_mini(char const *s, char c);

// 	QUOTES
int aux_quotes(char *lin);
int quotes(char *line);
char *get_clean_command(char *line, int *end_index);
int pipes_counter(char *line);

//STRUCT
char *ft_strjoin_mini(int len, t_com *commands);
t_com *create_struct(char *line, t_pipes pipes);
void init_struct(char *line, char *cmd, int end, t_com *commands);


#endif