/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 18:45:58 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_function(t_com *list, t_vars *vars)
{ // Ya funciona correctamente :)))
	t_env	*env_list;
	char	*line;

	if (!vars->env)
		return;
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
    char *equals_pos; // Puntero para buscar el símbolo '='
    int i;
	
    i = 0;
    if (!list->args || !*list->args) // Verificar si no hay argumentos: solo "export"
        return(free(list->args), print_export_vars(list, vars));
    while (list->args && list->args[i]) // Procesar cada argumento individualmente
    {
        equals_pos = ft_strchr(list->args[i], '='); // Buscar símbolo '=' en el argumento actual
        if (equals_pos) // Solo procesar argumentos con formato VAR=valor
            add_env_var(list->args[i], vars); // Añadir variable al entorno
		else // Formato VAR (sin valor)
			export_existing_var(list->args[i], vars);
        i++; // Si no tiene '=', ignorar
    }
    ft_free_free(list->args);
	list->args = NULL;
}

void unset_function(t_com *list, t_vars *vars)
{
	char **args;
    int i;
    int var_index;

	i = 0;
    if (!list->args || !*list->args) // Si no hay argumentos, no hacer nada
        return;
    if (!list->args)
        return;
    while (list->args[i]) // Procesar cada variable a eliminar
    {
        if (ft_strlen(list->args[i]) > 0) // Validar que sea un nombre de variable válido
        {
            var_index = find_env_var(list->args[i], vars); // Buscar la variable en el entorno usando tu función
            if (var_index != -1)
                remove_env_var(vars->env, var_index); // Eliminar la variable del entorno
        } // No hay error si la variable no existe
        i++;
    }
    ft_free_free(list->args); // Liberar memoria de los argumentos
	list->args = NULL;
}
