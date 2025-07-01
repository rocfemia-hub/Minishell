/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/07/01 16:35:17 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./Helicopter/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct s_vars
{
	int argc; //añadiendo argc y argv para tenerlos siempre a mano.
	char **argv;
	char **env;
	int fd_in; 
	int fd_out; 
} t_vars;

typedef struct s_com
{
	struct s_com *previous;
	char *command; // ej: "ls"
	char *command_arg; // ej: "ls -la"
	char *arg; // ej: "-la"
	char *path_command; // ej: "/usr/bin/ls"
	int index; //para saber en que nodo de la lista estas
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


// UTILS_BUILT-INS
int		valid_n_option(char *str);
int		valid_number(char *str);


/*PARSER*/ 


// TOKEN.C
t_com *token(char *line);
void *init_commands(char **commands, t_com *temp);
void *how_is(char *line, t_com *temp);
t_com *init_struct(char *line);
int pipes_counter(char *line);


// SPLIT_MINI.C
char	**ft_split_mini(char const *s, char c);

// COMMANDS1
void echo_com(t_com *temp, char *line);
void pwd_com(t_com *temp, char *line);
void cd_com(t_com *temp, char *line);
void export_com(t_com *temp, char *line);
void unset_com(t_com *temp, char *line);

// COMMANDS2
void env_com(t_com *temp, char *line);
void exit_com(t_com *temp, char *line);
void *not_built(t_com *temp, char *line);

// UTILS_COMMAND
int quotes(char *line,t_com *command);
int aux_quotes(char *line);
int quotes_in_commands(char *line, t_com *temp);
// int pipes_quotes(char *line);


#endif