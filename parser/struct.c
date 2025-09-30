/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:22:51 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:23:16 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **ft_strjoin_cmd_arg(t_com *commands)
{
    int j;
    int len;
    char **aux;
    int i;

    j = -1;
    if (commands->command)
        len = 1;
    while (commands->args[++j])
        len++;
    aux = ft_calloc(len + 1, sizeof(char *));
    j = -1;
    if (commands->command)
    {
        i = 1;
        aux[0] = ft_strdup(commands->command);
        while (commands->args[++j])
        {
            aux[i] = ft_strdup(commands->args[j]);
            i++;
        }
    }
    else
    {
        i = 0;
        while (commands->args[++j])
        {
            aux[i] = ft_strdup(commands->args[j]);
            i++;
        }
    }
    return (aux);
}

t_com *create_struct(char *line)
{ // create nodes list
    int i;
    int pipes;
    t_com *new;
    t_com *head;

    i = 0;
    pipes = look_for_char(line, 124); // counter pipes
    if (pipes < 0)
    {
        head = lstnew(i);
        head->error = ft_strdup("bash: open quote error");
        return (head);
    }
    head = lstnew(i);
    while (++i <= pipes) // create nodes
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
    char *new_line;
    if (!cmd || !line)
        return;
    commands->command = ft_substr(cmd, 0, ft_strlen(cmd) + 1);
    while (line[end] == ' ')
        end++;
    if (ft_strnstr(line + end, "$", ft_strlen(line + end)))
    {
        new_line = expand_args(line + end);
        commands->args = ft_split_parser(new_line);
        redirects(commands); // manage redirects
    }
    else
    {
        keep_quotes_args(commands, line + end);
        redirects(commands);            // manage redirects
        clean_quotes_in_args(commands); // crea un char **args dentro de commands
    }
    if (!ft_strncmp(commands->command, "echo", 4) || !ft_strncmp(commands->command, "pwd", 3) || !ft_strncmp(commands->command, "cd", 2) ||
        !ft_strncmp(commands->command, "exit", 4) || !ft_strncmp(commands->command, "env", 3) || !ft_strncmp(commands->command, "export", 6) ||
        !ft_strncmp(commands->command, "unset", 5))
        commands->flag_built = 1;
    commands->command_arg = ft_strjoin_cmd_arg(commands);
}