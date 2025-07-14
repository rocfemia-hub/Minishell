/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 02:24:15 by roo               #+#    #+#             */
/*   Updated: 2025/07/14 17:24:34 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *how_is(char *line, t_com *temp) // me mira que es cada cosa y llama a las funciones que lo va a meter en la estructura
{
	char *spaces;
	int i;
	
	i = 0; 
	if (!line || !temp) // implementando esta función paara que funcionen los built-in
        return (NULL);
	spaces = ft_strtrim(line, " \t");
    if (!spaces)
        return (NULL);
	while (spaces[i] == ' ' || spaces[i] == '\t')
        i++;
    if (ft_strncmp(spaces + i, "echo", 4) == 0 && (spaces[i + 4] == ' ' || spaces[i + 4] == '\0')) // Verifica comando al inicio de la línea
        echo_com(temp, spaces);
    else if (ft_strncmp(spaces + i, "pwd", 3) == 0 && (spaces[i + 3] == ' ' || spaces[i + 3] == '\0'))
        pwd_com(temp, spaces);
    else if (ft_strncmp(spaces + i, "cd", 2) == 0 && (spaces[i + 2] == ' ' || spaces[i + 2] == '\0'))
        cd_com(temp, spaces);
    else if (ft_strncmp(spaces + i, "env", 3) == 0 && (spaces[i + 3] == ' ' || spaces[i + 3] == '\0'))
        env_com(temp, spaces);
    else if (ft_strncmp(spaces + i, "exit", 4) == 0 && (spaces[i + 4] == ' ' || spaces[i + 4] == '\0'))
        exit_com(temp, spaces);
    else
        not_built(temp, spaces); // para que siempre asigne algo
    return (free(spaces), NULL);
}

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
