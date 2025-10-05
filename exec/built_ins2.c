/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/10/05 20:00:57 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_function(t_com *list, t_vars *vars)
{ // Ya funciona correctamente :)))
	t_env	*env_list;
	char	*line;

	if (!vars->env)
		return;
	env_list = vars->env_list;
	while (env_list)
	{
		line = ft_strjoin(env_list->env_name, "=");
        line = ft_strjoin_gnl(line, env_list->env_inf);
		write(list->fd_out, line, ft_strlen(line));
        write(list->fd_out, "\n", 1);
		free(line);
        env_list = env_list->next;
	}
}

void export_function(t_com *list, t_vars *vars)
{ //¡¡¡NO FUNCIONA BIEN, si metes espacios en las variables, te hace dos variables distintas("hola) por un lado y (mundo") por otro.!!!
	//char **args; // TIENE FUGAS DE MEMORIA "export MY_VAR=bye"
    int i;
	
    i = 0;
    if (!list->args || !*list->args) // Verificar si no hay argumentos: solo "export"
        return(free(list->args), print_export_vars(list, vars));
    while (list->args && list->args[i]) // Procesar cada argumento por separado
    {
		if (!valid_var_name(list->args[i])) 
        {
            ft_putstr_fd("export: '", 2);
            ft_putstr_fd(list->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
		else
			add_update_env_var(vars, list->args[i]);
        i++;
    }
    ft_free_free(list->args);
	list->args = NULL;
}

void unset_function(t_com *list, t_vars *vars)
{
    int i;
    
	i = 0;
    if (!list->args || !*list->args)
        return;
    while (list->args[i])
    {
        if (valid_var_name(list->args[i])) 
        {
            remove_env_var(vars, list->args[i]); // Eliminar de la lista de entorno
            remove_in_env_array(vars, list->args[i]); // También eliminar del array de entorno
        }
        else 
        {
            ft_putstr_fd("unset: '", 2);
            ft_putstr_fd(list->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
        i++;
    }
    ft_free_free(list->args); // Liberar memoria de los argumentos
	list->args = NULL;
}
