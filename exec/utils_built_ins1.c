/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:44:29 by roo               #+#    #+#             */
/*   Updated: 2025/10/29 16:20:38 by roo              ###   ########.fr       */
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
    t_env *env_list;
    char *line;

    env_list = vars->env_list;
    while (env_list)
    {
        write(list->fd_out, "declare -x ", 11);
        line = ft_strjoin(env_list->env_name, "="); // Crear línea "NOMBRE=valor"
        line = ft_strjoin_gnl(line, env_list->env_inf);
        write(list->fd_out, line, ft_strlen(line));
        write(list->fd_out, "\n", 1);
        free(line);
        env_list = env_list->next;
    }
}

void remove_env_var(t_vars *vars, char *name)
{
    t_env *env_list;
    t_env *prev;

	env_list = vars->env_list;
	prev = NULL;
    while (env_list)
    {
        if (ft_strncmp(env_list->env_name, name, ft_strlen(env_list->env_name)) == 0)
        {
            if (prev)
                prev->next = env_list->next;
            else
                vars->env_list = env_list->next;
                
            free(env_list->env_name);
            free(env_list->env_inf);
            free(env_list);
            return;
        }
        prev = env_list;
        env_list = env_list->next;
    }
}

void cd_aux_funcion(t_com *list, t_vars *vars, char *old_pwd)
{ // Actualizar PWD y OLDPWD en el entorno
	char *new_dir;
	char *new_pwd;
	
    add_update_env_var(vars, old_pwd);
    free(old_pwd);

    new_dir = getcwd(NULL, 0); // Obtener y actualizar el PWD
    new_pwd = ft_strjoin("PWD=", new_dir);
    add_update_env_var(vars, new_pwd);

    free(new_dir);
    free(new_pwd);

    if (list->args) 
	{
        ft_free_free(list->args);
        list->args = NULL;
    }
}
