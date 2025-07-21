/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:29 by roo               #+#    #+#             */
/*   Updated: 2025/07/20 00:09:41 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int valid_n_option(char *str)
{
    int i;
    
    if (!str || str[0] != '-' || !str[1])
        return (0);
    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int valid_number(char *str)
{
    int i = 0;
    
    if (!str || !*str)
        return (0);
    while (str[i] == ' ') // Saltar espacios iniciales
        i++;
    if (str[i] == '+' || str[i] == '-') // Permitir signo opcional
        i++;
    if (!str[i]) // Debe haber al menos un dígito después del signo
        return (0);
    while (str[i]) // Verificar que todos los caracteres restantes sean dígitos
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    
    return (1);
}

void print_export_vars(t_com *list, t_vars *vars)
{
    int i;
    
    i = 0;
    while (vars->env[i])
    {
        write(list->fd_out, "declare -x ", 11); // Escribir prefijo estándar de bash para variables exportadas
        write(list->fd_out, vars->env[i], ft_strlen(vars->env[i])); // Escribir la variable completa (formato: VAR=valor)
        write(list->fd_out, "\n", 1); // Añadir salto de línea después de cada variable
        i++;
    }
}

void remove_env_var(char **env, int index)
{
    int i;

	i = index; // Mover todas las entradas una posición hacia atrás
    if (!env || index < 0)
        return;
    free(env[index]);
    while (env[i + 1])
    {
        env[i] = env[i + 1];
        i++;
    }
    env[i] = NULL;
}
