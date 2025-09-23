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

int aux_ft_strjoin_mini(t_com *commands)
{
    char *cmd_arg;
    int len;
    int k;

    len = 0;
    len += ft_strlen(commands->command) + 1;
    k = -1;
    while (commands->args && commands->args[++k])
        len += ft_strlen(commands->args[k]) + 1;
    return(len);
}

char *ft_strjoin_mini(t_com *commands)
{
    int i;
    int j;
    int k;
    char *cmd_arg;

    cmd_arg = ft_calloc(aux_ft_strjoin_mini(commands) + 1, sizeof(char));
    if (!cmd_arg)
        return (NULL);
    i = 0;
    j = 0;
    while (commands->command[i])
        cmd_arg[j++] = commands->command[i++];
    cmd_arg[j++] = ' ';
    k = -1;
    while (commands->args && commands->args[++k])
    {
        i = 0;
        while (commands->args[k][i])
            cmd_arg[j++] = commands->args[k][i++];
        cmd_arg[j++] = ' ';
    }
    if (j > 0 && cmd_arg[j - 1] == ' ')
        j--;
    commands->command_arg = cmd_arg;
    return (cmd_arg);
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
        new_line = expand_args(line);
        commands->args = ft_split_parser(new_line);
        redirects(commands); // manage redirects
    }
    else
    {
        keep_quotes_args(commands, line + end);
        redirects(commands);     // manage redirects
        clean_quotes_in_args(commands); // crea un char **args dentro de commands
    }
    if (!ft_strncmp(commands->command, "echo", 4) || !ft_strncmp(commands->command, "pwd", 3) || !ft_strncmp(commands->command, "cd", 2) ||
        !ft_strncmp(commands->command, "exit", 4) || !ft_strncmp(commands->command, "env", 3) || !ft_strncmp(commands->command, "export", 6) ||
        !ft_strncmp(commands->command, "unset", 5))
        commands->flag_built = 1;
    ft_strjoin_mini(commands); // join arg and cmd in a char *comands_arg
}