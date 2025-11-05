/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:11:00 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:54:30 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int aux_parser_redirects(t_com *commands, char *redirect, int type)
{
	char *tmp_file;

	if (!commands->args[commands->redirects->j + 1])
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1) || ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1))
	{
		if (ft_strnstr(commands->args[commands->redirects->j + 1], ">", 1))
			commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
		else if (ft_strnstr(commands->args[commands->redirects->j + 1], "<", 1)) 
			commands->error = ft_strdup("bash: syntax error near unexpected token `<'");
		commands->vars->exit_status = 2;
		return (0);
	}
	tmp_file = ft_strdup(commands->args[commands->redirects->j + 1]);
	fill_type_redirect(commands, type);
	commands->args = copy_redirect_matrix(commands->args, commands->redirects->j, commands->redirects->j + 1);
	fill_cmd(commands, redirect, tmp_file);
	return (1);
}

char *find_redirect_position(char *arg, char *redirect)
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
			return (arg + i);
		i++;
	}
	return (NULL);
}

int parser_redirects(t_com *commands, char *redirect, int type)
{
	char *tmp_file;
	char *redirect_pos;
	char *before_redirect;
	int pos;

	if (ft_strnstr(commands->args[commands->redirects->j], ">>>", 3)) // error >>>
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `>'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strnstr(commands->args[commands->redirects->j], "<<<", 3)) // error hola< y <<<
	{
		commands->error = ft_strdup("bash: syntax error near unexpected token `newline'");
		commands->vars->exit_status = 2;
		return (0);
	}
	else if (ft_strlen(commands->args[commands->redirects->j]) > ft_strlen(redirect)) // si la redireccion esta asi ">adios" o "hola>adios"
	{
		redirect_pos = find_redirect_position(commands->args[commands->redirects->j], redirect);
		if (redirect_pos)
		{
			tmp_file = ft_strdup(redirect_pos + ft_strlen(redirect)); // archivo al que redirecciona
			pos = redirect_pos - commands->args[commands->redirects->j];               // posicion del redirect en el string
			if (pos > 0)                                                               // hay texto antes de la redireccion "hola>adios"
			{
				before_redirect = ft_calloc(pos + 1, sizeof(char));
				ft_strlcpy(before_redirect, commands->args[commands->redirects->j], pos + 1);
				free(commands->args[commands->redirects->j]);
				commands->args[commands->redirects->j] = before_redirect; // reemplazar "hola>adios" por "hola"
				fill_type_redirect(commands, type);
				commands->args = copy_redirect_matrix(commands->args, -1, -1);
				fill_cmd(commands, redirect, tmp_file);
			}
			else // la redireccion esta al inicio ">adios"
			{
				fill_type_redirect(commands, type);
				commands->args = copy_redirect_matrix(commands->args, commands->redirects->j, commands->redirects->j);
				fill_cmd(commands, redirect, tmp_file);
			}
		}
		else
		{
			tmp_file = ft_strdup(commands->args[commands->redirects->j] + ft_strlen(redirect));
			fill_type_redirect(commands, type);
			commands->args = copy_redirect_matrix(commands->args, commands->redirects->j, commands->redirects->j);
			fill_cmd(commands, redirect, tmp_file);
		}
	}
	else // el archivo esta separado del simbolo "hola > adios"
		if (!aux_parser_redirects(commands, redirect, type))
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

	if (!commands->args || !commands->redirects || commands->redirects->j) // COMPROBAR Q EXISTE (HOLA BUENOS DIAS HE CAMBIADO QUE CHECKIE QUE NO HAYA "J" JAJA HOLA)
		return;
	while (commands->args[commands->redirects->j])
	{
		if (is_redirect_token(commands->args[commands->redirects->j], ">>"))
		{
			if (!parser_redirects(commands, ">>", 3))
				return;
			commands->redirects->j = -1;
		}
		else if (is_redirect_token(commands->args[commands->redirects->j], "<<"))
		{
			if (!parser_redirects(commands, "<<", 4))
				return;
			commands->redirects->j = -1;
		}
		else if (is_redirect_token(commands->args[commands->redirects->j], ">"))
		{
			if (!parser_redirects(commands, ">", 2))
				return;
			commands->redirects->j = -1;
		}
		else if (is_redirect_token(commands->args[commands->redirects->j], "<"))
		{
			if (!parser_redirects(commands, "<", 1))
				return;
			commands->redirects->j = -1;
		}
		else if (ft_strnstr(commands->args[commands->redirects->j], "<<", ft_strlen(commands->args[commands->redirects->j])) || ft_strnstr(commands->args[commands->redirects->j], ">>", ft_strlen(commands->args[commands->redirects->j])) ||
				 ft_strnstr(commands->args[commands->redirects->j], "<", ft_strlen(commands->args[commands->redirects->j])) || ft_strnstr(commands->args[commands->redirects->j], ">", ft_strlen(commands->args[commands->redirects->j])))
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
	if (!commands->redirects)
		return;
	if (is_redirect_token(commands->command, "<") || is_redirect_token(commands->command, "<<") || is_redirect_token(commands->command, ">") || is_redirect_token(commands->command, ">>"))
		if (!redirects_cmd(commands))
			return;
	find(commands);
}
