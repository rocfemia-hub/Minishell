/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:58:55 by roo               #+#    #+#             */
/*   Updated: 2025/06/13 17:05:59 by roo              ###   ########.fr       */
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

typedef struct s_com
{
	struct s_com *previous;
	char *command;
	char *command_arg;
	char *arg;
	char *path_command;
	int fd_in; 
	int fd_out; 
	int index;
	int flag_built; // 1 para built 0 execve
	struct s_com *next;
}	t_com;



/*MIX*/ 

// MAIN

void commands_control(t_com *vars);
int line_break(char *line);

//LISTAS

t_com *lstnew(int index);
void	lstadd_back(t_com **lst, t_com *new);
void print_stack(t_com *stack);

//ERROR
void printf_matrix(char **split);



/*EXEC*/ 

// BUILT-INS

void echo_function(t_com *vars);
void pwd_function(t_com *vars);

// BUILT-INS
int salto_linea(char *line);



/*PARSER*/ 

// PARSER.C
t_com *token(char *line);
void *init_commands(char **commands, t_com *temp);
void *how_is(char *line, t_com *temp);
t_com *init_struct(char **commands);

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



#endif