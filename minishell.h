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

typedef struct vars
{
	char **params;
	int output_fd;
	int input_fd;
	int exit_status;
} t_vars;

typedef struct s_com
{
	struct s_com *previous;
	char **command;
	char *path_command;
	int fd_in; 
	int fd_out; 
	int index;
	int flag_built; // 1 para built 0 execve
	struct s_com *next;
}	t_com;

// MAIN

void commands_control(t_vars *vars);

// BUILT-INS

void echo_function(t_vars *vars);
void pwd_function(t_vars *vars);

// PARSER
int parser(char *line);

//SPLIT
char	**ft_split_new(char const *s);

//LISTAS
void	lstadd_back(t_com **lst, t_com *new);
t_com *lstnew(void *content);

//ERROR
void printf_matrix(char **split);

#endif