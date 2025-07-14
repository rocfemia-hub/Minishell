/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/07/11 21:31:33 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_function(t_com *list, t_vars *vars)
{ // Ya funciona correctamente :)))
	int i = 0;

	if (!vars->env)
		return;
	while (vars->env[i])
	{
		write(list->fd_out, vars->env[i], ft_strlen(vars->env[i])); // simplemente imprime linea a linea lo que hay en el env, sin opciones ni argmentos (lo pone en el subject)
		write(list->fd_out, "\n", 1);
		i++;
	}
}

void export_function(t_com *list, t_vars *vars)
{}

void unset_function(t_com *list, t_vars *vars)
{}
