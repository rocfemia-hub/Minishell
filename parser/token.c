/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 02:24:15 by roo               #+#    #+#             */
/*   Updated: 2025/07/04 03:19:19 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*t_com *init_struct(char *line) // me crea la lista donde voy a meter los index y los fd_out
{
    int i;
    int pipes;
    t_com *new_node;
    t_com *head;

	i = 1;
    pipes = 0;
    new_node = NULL;
    head = NULL;
	if (!line)
        return (NULL);
    pipes = pipes_counter(line); // me cuenta los pipes que hay, sin que sean argumentos
    //printf("pipes: %d\n", pipes);
    head = lstnew(0);
    if (!head)
        return (NULL);
    while (line[++i] && i < pipes + 1)
    {
        new_node = lstnew(i);
        if (!new_node)
            return (free_list(head), NULL);
        lstadd_back(&head, new_node);
    }
    return (head);
}*/

void *how_is(char *line, t_com *temp) // me mira que es cada cosa y llama a las funciones que lo va a meter en la estructura
{
	char *spaces; // para añadir espacios
	
	if (!line || !temp) // implementando esta función paara que funcionen los built-in
        return (NULL);
	spaces = ft_strtrim(line, " \t");
    if (!spaces)
        return (NULL);
    if (ft_strnstr(spaces, "echo", 4))
        echo_com(temp, spaces);
    else if (ft_strnstr(spaces, "pwd", 3))
        pwd_com(temp, spaces);
    else if (ft_strnstr(spaces, "cd", 2))
        cd_com(temp, spaces);
    else if (ft_strnstr(spaces, "env", 3))
        env_com(temp, spaces);
    else if (ft_strnstr(spaces, "exit", 4))
        exit_com(temp, spaces);
    else
        not_built(temp, spaces);  // para que siempre asigne algo
    return (free(spaces), NULL);
}

/*void *init_commands(char **commands /*split por pipes, t_com *temp) // me va llamando a la funcion que mira lo que es cada comando, pasando cada array de la matriz que hemos separado en pipes
{
    int i = 0;
	t_com *aux_temp; // añadiendo un auxiliar para el temp;

	aux_temp = temp;
	if (!aux_temp || !temp)
        return(NULL);
    while (aux_temp && commands[i])
    {
        how_is(commands[i], aux_temp);
        aux_temp = aux_temp->next;
        i++;
    }
}*/

t_com *token(char *line) // me separa la array de comandos, arg y flags en una estructura
{
    t_com *head; // Primer nodo de la lista
	t_com *new_node; // Nodo temporal para cada comando
	char **commands; // Array de comandos separados por pipes
	int i;

	if (!line)
        return (NULL);
	head = NULL;
    commands = ft_split(line, '|'); // Dividir primero por pipes
    if (!commands)
        return (NULL);
	head = NULL;
    i = 0;
	while (commands[i]) // gestionar cada comando de manera individual
    {
        new_node = lstnew(i);
        if (!new_node)
            return (ft_free_free(commands), free_list(head), NULL);
        how_is(commands[i], new_node); // parsear cada comando de manera individual
        if (!head) // primer nodo
            head = new_node;
        else
            lstadd_back(&head, new_node); // ir añadiendo a la lista
        i++;
    }
    return (ft_free_free(commands), head); // liberar arreay temporal y retornar la lista
}
