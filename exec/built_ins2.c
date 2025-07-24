/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/07/24 02:21:44 by roo              ###   ########.fr       */
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
{ //¡¡¡NO FUNCIONA BIEN, si metes espacios en las variables, te hace dos variables distintas("hola) por un lado y (mundo") por otro.!!!
	char **args; // TIENE FUGAS DE MEMORIA "export MY_VAR=bye"
    char *equals_pos; // Puntero para buscar el símbolo '='
    int i;
	
    i = 0;
    if (!list->args || !*list->args) // Verificar si no hay argumentos: solo "export"
        return(print_export_vars(list, vars));
    if (!list->args)  // Si el split falla, salir
        return;
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
