/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:18:22 by roo               #+#    #+#             */
/*   Updated: 2025/07/19 17:03:38 by roo              ###   ########.fr       */
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
{ //Funciona pero le faltan más pruebas (no se si ya funciona bien por completo) "export MY_VAR=bye"
	char **args;
    char *equals_pos; // Puntero para buscar el símbolo '='
    int i;
	
    i = 0;
    if (!list->arg || !*list->arg) // Verificar si no hay argumentos: solo "export"
        return(print_export_vars(list, vars));
    args = ft_split_mini(list->arg, ' '); // Dividir argumentos por espacios
    if (!args)  // Si el split falla, salir
        return;
    while (args[i]) // Procesar cada argumento individualmente
    {
        equals_pos = ft_strchr(args[i], '='); // Buscar símbolo '=' en el argumento actual
        if (equals_pos) // Solo procesar argumentos con formato VAR=valor
            add_env_var(args[i], vars); // Añadir variable al entorno
		else // Formato VAR (sin valor)
			export_existing_var(args[i], vars);
        i++; // Si no tiene '=', ignorar
    }
    ft_free_free(args);
} // (formato export VAR no implementado)

void unset_function(t_com *list, t_vars *vars)
{}
