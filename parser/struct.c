/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:51 by roo               #+#    #+#             */
/*   Updated: 2025/07/24 01:22:53 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_mini(t_com *commands)
{ //join cmd and arg --> cmd_arg
    int i;
    int j;
    int k;
    int len = 0;
    char *cmd_arg;

    len += ft_strlen(commands->command) + 1; 
    k = 0;
    while (commands->args && commands->args[k]) 
    {
        len += ft_strlen(commands->args[k]) + 1; 
        k++;
    }
    cmd_arg = ft_calloc(len + 1, sizeof(char));
    if (!cmd_arg)
        return (NULL);
    i = 0;
    j = 0;
    while (commands->command[i])
        cmd_arg[j++] = commands->command[i++];
    cmd_arg[j++] = ' ';
    k = 0;
    while (commands->args && commands->args[k])
    {
        i = 0;
        while (commands->args[k][i])
            cmd_arg[j++] = commands->args[k][i++];
        cmd_arg[j++] = ' ';
        k++;
    }
    if (j > 0 && cmd_arg[j - 1] == ' ')
        j--;
    commands->command_arg = cmd_arg;
    return (cmd_arg);
}

t_com *create_struct(char *line, t_pipes pipes)
{ // create nodes list 
    int i = 0;
    t_com *new;
    t_com *head; 

    pipes.pipes = pipes_counter(line); // counter pipes 
    if (pipes.pipes < 0)
        return (NULL);
    head = lstnew(i);
    if (!head)
        return (NULL);
    while (++i <= pipes.pipes) // create nodes
    {
        new = lstnew(i);
        if (!new)
            return (NULL);
        lstadd_back(&head, new);
    }
    return (head);
}

void init_struct(char *line, char *cmd, int end, t_com *commands)
{ // init commands and arg
    int len;

    if (!cmd || !line)
        return;
    commands->command = ft_substr(cmd, 0, ft_strlen(cmd) + 1);
    while (line[end] == ' ')
        end++;
    clean_and_fill_arg(commands, line + end); // create double array and fill it in arg
    if (!ft_strncmp(commands->command, "echo", 4) || !ft_strncmp(commands->command, "pwd", 3) || !ft_strncmp(commands->command, "cd", 2) ||
        !ft_strncmp(commands->command, "exit", 4) || !ft_strncmp(commands->command, "env", 3) || !ft_strncmp(commands->command, "export", 6) ||
            !ft_strncmp(commands->command, "unset", 5))
        commands->flag_built = 1;
    ft_strjoin_mini(commands); // join arg and cmd in a char *comands_arg
    redirects(commands); // manage redirects
}

