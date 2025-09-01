/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/09/01 15:56:23 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void set_redirections(t_com *list)
{
	if (list->redirects == NULL)
		return;
    if (list->redirects->output_file) // Redirección de salida > "¿Hay un archivo para escribir?"
    {
        list->fd_out = open(list->redirects->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644); //Crear archivo si no existe, solo escritura, sobreescribir, permisos: propietario lee/escribe, otros solo leen
        if (list->fd_out == -1)
            return(perror("Error opening output file"));
    }
    if (list->redirects->input_file) // Redirección de entrada "¿Hay un archivo para leer?"
    {
        list->fd_in = open(list->redirects->input_file, O_RDONLY); // archivo d solo lectura
        if (list->fd_in == -1)
            return(perror("Error opening input file"));
    }
    if (list->redirects->append_file) // Append >> "¿Hay archivo para añadir?"
    {
        list->fd_out = open(list->redirects->append_file, O_CREAT | O_WRONLY | O_APPEND, 0644); // la diferencia entre O_APPEND con O_TRUNC es q no borra contenido existente, slo escribe al final del archivo
        if (list->fd_out == -1)
            return(perror("Error opening append file"));
    }
	clean_fds(list);
}

void clean_fds(t_com *list)
{
    if (list->fd_in != 0)
        close(list->fd_in);
    if (list->fd_out != 1)
        close(list->fd_out);
	list->fd_in = 0;
    list->fd_out = 1;
}
