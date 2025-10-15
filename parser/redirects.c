/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/10/15 15:23:28 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int aux_parser_redirects(t_com *commands, char *redirect)
{
    if (!commands->args[commands->redirects->j + 1]) // no hay archivo al que redireccionar
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
        commands->vars->exit_error = 2;
        return (0);
    }
    if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1) || ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1)) // dos operadores juntos > >
    {
        //printf("entra\n");
        if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1))
            commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
        else if (ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1)) // ELSE IF
            commands->error = ft_strdup("bash: syntax error near unexpected token `<'");
        commands->vars->exit_error = 2;
        return (0);
    }
    commands->redirects->file = ft_strdup(commands->args[commands->redirects->j + 1]); // archivo al que redirecciona
    fill(commands, commands->redirects->j, commands->redirects->j + 1, redirect);      // rellena estructura
    return (1);
}

int parser_redirects(t_com *commands, char *redirect)
{                                                                     // chequear si despues de la redireccion hay archivo o antes
    if (ft_strnstr(commands->args[commands->redirects->j], ">>>", 3)) // error >>>
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
        commands->vars->exit_error = 2;
        return (0);
    }
    else if (commands->args[commands->redirects->j][0] != redirect[0] || ft_strnstr(commands->args[commands->redirects->j], "<<<", 3)) // error hola< y <<<
    {
        commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
        commands->vars->exit_error = 2;
        return (0);
    }
    else if (ft_strlen(commands->args[commands->redirects->j]) > ft_strlen(redirect)) // si la redireccion esta asi ">adios" --> no es error
    {
        commands->redirects->file = ft_strdup(commands->args[commands->redirects->j] + ft_strlen(redirect)); // archivo al que redirecciona
        fill(commands, commands->redirects->j, commands->redirects->j, redirect);                            // rellena estructura
    }
    else // el archivo esta separado del simbolo "hola > adios"
        if (!aux_parser_redirects(commands, redirect))
            return (0);
    return (1);
}

char *clean_quotes_in_line(char *arg)
{
    int j = 0;
    int k = 0;
    char *new_arg;
    char quote = 0;

    if (!arg)
        return (NULL);

    new_arg = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
    if (!new_arg)
        return (NULL);

    while (arg[j])
    {
        if (arg[j] == '\'' || arg[j] == '"')
        {
            if (quote == 0)
                quote = arg[j];
            else if (quote == arg[j])
                quote = 0;
            else
                new_arg[k++] = arg[j]; 
        }
        else
            new_arg[k++] = arg[j];
        j++;
    }
    new_arg[k] = '\0';
    free(arg);
    return (new_arg);
}

int is_redirect_token(char *arg, char *redirect)
{
    int i;
    int quote;

    i = 0;
    quote = 0;
    while (arg[i])
    {
        if (arg[i] == '\'' || arg[i] == '"')
        {
            if (quote == 0)
                quote = arg[i];
            else if (quote == arg[i])
                quote = 0;
        }
        else if (!quote && ft_strncmp(arg + i, redirect, ft_strlen(redirect)) == 0)
            return (1);
        i++;
    }
    return (0);
}

void find(t_com *commands)
{ // look for < or >
	char *temp;
	
	if (!commands->args || !commands->redirects) //COMPROBAR Q EXISTE
        return;
    while (commands->args[commands->redirects->j])
    {
        if (is_redirect_token(commands->args[commands->redirects->j], ">>"))
        {
            if (!parser_redirects(commands, ">>"))
                return;
            commands->redirects->j = -1;
        }
        else if (is_redirect_token(commands->args[commands->redirects->j], "<<"))
        {
            if (!parser_redirects(commands, "<<"))
                return;
            commands->redirects->j = -1;
        }
        else if (is_redirect_token(commands->args[commands->redirects->j], ">"))
        {
            if (!parser_redirects(commands, ">"))
                return;
            commands->redirects->j = -1;
        }
        else if (is_redirect_token(commands->args[commands->redirects->j], "<"))
        {
            if (!parser_redirects(commands, "<"))
                return;
            commands->redirects->j = -1;
        }
        else
        {
            temp = commands->args[commands->redirects->j];
            commands->args[commands->redirects->j] = clean_quotes_in_line(temp);
        }
        commands->redirects->j++;
    }
}

void redirects(t_com *commands)
{
    commands->redirects = ft_calloc(1, sizeof(t_red)); // redirect struct
	if(!commands->redirects)
		return;
    if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">") || is_redirect_token(commands->command, ">>"))
        if (!redirects_cmd(commands))
            return;
    find(commands);
}
