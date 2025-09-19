/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:23:04 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:23:40 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void type_command(char *line, t_com *commands)
{
    t_clean_cmd data;

    ft_bzero(&data, sizeof(t_clean_cmd));
    data.cmd = only_cmd(line, &data);
    if (ft_strnstr(data.cmd, "$", ft_strlen(data.cmd)))
        expand_cmd(&data);
    else
        data.cmd = clean_cmd(data.cmd, &data); // cmd without quotes
    init_struct(line, data.cmd, data.end_index, commands); //fill cmd and arg
    free(data.cmd); // LIBERAR TODO DATA, SOLO HAY UN CHAR * RESTO SON INT
}

void init_commands(char *line, t_com *commands)
{
    int i = 0;
    int start = 0;
    char quote = 0;
    t_com *current = commands;

    while (line[i])
    {
        if ((line[i] == '"' || line[i] == '\''))
        {
            if (!quote) // quotes open or closed
                quote = line[i];
            else if (quote == line[i])
                quote = 0;
        }
        if (line[i] == '|' && !quote) // < << >> <
        {
            line[i] = '\0';
            type_command(line + start, current);
            start = i + 1;
            current = current->next;
        }
        i++;
    }
    if (current) // last command and arg
        type_command(line + start, current);
    // LIBERAR CURRENT 
}

t_com *token(char *line) 
{
    t_com *commands;

    commands = create_struct(line);
    if (commands->error)
    {
        error(commands);
        return (NULL);
    }
    init_commands(line, commands);
    if (commands->error)
    {
        error(commands);
        return (NULL);
    }
    printf("\033[34mprint_list:\033[0m\n");
    print_list(commands);
    printf("\033[34mprint_redirects:\033[0m\n");
    // printf("append_file: %s, flag: %d\n", commands->redirects->append_file[0], commands->redirects->redirect_append);
    // printf("input_file: %s, flag: %d\n", commands->redirects->input_file[0], commands->redirects->redirect_in);
    // printf("output_file: %s, flag: %d\n", commands->redirects->output_file[0], commands->redirects->redirect_out);
    // printf("output_file: %s, flag: %d\n", commands->redirects->output_file[1], commands->redirects->redirect_out);
    printf("\033[34mejecutor\033[0m\n");
    return (commands);
}
