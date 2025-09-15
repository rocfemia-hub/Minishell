/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:48:52 by roo               #+#    #+#             */
/*   Updated: 2025/09/15 21:01:35 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void set_redirections(t_com *list)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 0;
	if (list->redirects == NULL)
		return;
	if (list->redirects->redirect_heredoc) //el heredoc toma prioridad sobre otras redirecciones de input
	{
		heredoc_execution(list);
    	return;
	}
	while(list->redirects->redirect_in && list->redirects->input_file[i + 1]) //list->redirects->redirect_in Esto se comprueba antes?
		i++; // esto es para recorrer la matriz de cada redirección
	while(list->redirects->redirect_out && list->redirects->output_file[j + 1]) // ... igual q arriba
		j++;
	while(list->redirects->redirect_append && list->redirects->append_file[k + 1]) // ...
		k++;
    if (list->redirects->redirect_out && list->redirects->output_file[j]) // Redirección de salida > "¿Hay un archivo para escribir?"
    {
        list->fd_out = open(list->redirects->output_file[j], O_CREAT | O_WRONLY | O_TRUNC, 0644); //Crear archivo si no existe, solo escritura, sobreescribir, permisos: propietario lee/escribe, otros solo leen
        if (list->fd_out == -1)
            return(perror("Error opening output file"));
    }
    if (list->redirects->redirect_in && list->redirects->input_file[i]) // Redirección de entrada "¿Hay un archivo para leer?"
    {
        list->fd_in = open(list->redirects->input_file[i], O_RDONLY); // archivo d solo lectura
        if (list->fd_in == -1)
            return(perror("Error opening input file"));
    }
    if (list->redirects->redirect_append && list->redirects->append_file[k]) // Append >> "¿Hay archivo para añadir?"
    {
        list->fd_out = open(list->redirects->append_file[k], O_CREAT | O_WRONLY | O_APPEND, 0644); // la diferencia entre O_APPEND con O_TRUNC es q no borra contenido existente, slo escribe al final del archivo
        if (list->fd_out == -1)
            return(perror("Error opening append file"));
    }
	//clean_fds(list); NO SE COMO LLAMAR A ESTO SIN RESETEAR AUXILIO
}

void heredoc_execution(t_com *list)
{
    int pipe_fd[2];
    pid_t pid;
    if (pipe(pipe_fd) == -1) // Crear pipe para el heredoc
        return(perror("pipe heredoc"));
    
    pid = fork();
    if (pid == 0) // PROCESO HIJO: escribir contenido del heredoc
    {
        close(pipe_fd[0]); // Cerrar lectura
        write_heredoc(pipe_fd[1], list);
        close(pipe_fd[1]);
        exit(0);
    }
    else if (pid > 0) // PROCESO PADRE: configurar input
    {
        close(pipe_fd[1]); // Cerrar escritura
        list->fd_in = pipe_fd[0]; // El comando leerá del pipe
        waitpid(pid, NULL, 0);
    }
    else
        perror("fork heredoc");
}

void write_heredoc(int write_fd, t_com *list)
{ // ES UNA PRUEBA (Leer el contenido almacenado del heredoc - Escribirlo línea por línea al pipe)
    char *test_content = "linea1\nlinea2\nlinea3\n";
    write(write_fd, test_content, strlen(test_content));
}

void clean_fds(t_com *list)
{
    if (list->fd_in != 0)
        close(list->fd_in);
    if (list->fd_out != 1)
        close(list->fd_out);
	//list->fd_in = 0;
    //list->fd_out = 1;
}
