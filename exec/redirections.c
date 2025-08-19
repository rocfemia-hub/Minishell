/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/08/19 20:19:26 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void set_redirections(t_com *cmd)
{
    if (cmd->output_file) // Redirección de salida > "¿Hay un archivo para escribir?""
    {
        cmd->fd_out = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644); //Crear archivo si no existe, solo escritura, sobreescribir, permisos: propietario lee/escribe, otros solo leen
        if (cmd->fd_out == -1)
            return(perror("Error opening output file"));
    }
    if (cmd->input_file) // Redirección de entrada "¿Hay un archivo para leer?"
    {
        cmd->fd_in = open(cmd->input_file, O_RDONLY); // archivo d solo lectura
        if (cmd->fd_in == -1)
            return(perror("Error opening input file"));
    }
    if (cmd->append_file) // Append >> "¿Hay archivo para añadir?"
    {
        cmd->fd_out = open(cmd->append_file, O_CREAT | O_WRONLY | O_APPEND, 0644); // la diferencia entre O_APPEND con O_TRUNC es q no borra contenido existente, slo escribe al final del archivo
        if (cmd->fd_out == -1)
            return(perror("Error opening append file"));
    }
}

void clean_fds(t_com *cmd)
{
    if (cmd->fd_in != 0)
        close(cmd->fd_in);
    if (cmd->fd_out != 1)
        close(cmd->fd_out);
}
