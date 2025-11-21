/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/17 18:13:39 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_char_protect(char c)
{
	if (c == 32 || c == '\t' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

void	fill_red(t_com *commands, char *redirect, char *file)
{
	if (ft_strncmp(redirect, "<<", 3) == 0)
	{
		if (commands->redirects->delimiter)
			free(commands->redirects->delimiter);
		commands->redirects->delimiter = clean_quotes_in_line(ft_strdup(file),
				&commands->quoted);
		commands->redirects->redirect_heredoc = 1;
	}
	else if (ft_strncmp(redirect, ">>", 3) == 0)
		handle_redirect_array(&commands->redirects->append_file,
			&commands->redirects->redirect_append, file, commands);
	else if (ft_strncmp(redirect, "<", 2) == 0)
		handle_redirect_array(&commands->redirects->input_file,
			&commands->redirects->redirect_in, file, commands);
	else if (ft_strncmp(redirect, ">", 2) == 0)
		handle_redirect_array(&commands->redirects->output_file,
			&commands->redirects->redirect_out, file, commands);
	free(file);
}

char	**realloc_redirect_args(char **flag)
{
	int		i;
	int		j;
	char	**realloc_matrix;

	j = 0;
	while (flag[j])
		j++;
	realloc_matrix = ft_calloc(j, sizeof(char *));
	if (!realloc_matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (flag[++i])
	{
		realloc_matrix[j] = ft_strdup(flag[i]);
		j++;
	}
	ft_free_free(flag);
	return (realloc_matrix);
}

char	**redirect_args(t_com *commands)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	while (commands->args && commands->args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i);
	if (!new_args)
		return (NULL);
	i = 1;
	j = 0;
	while (commands->args && commands->args[i])
	{
		new_args[j] = commands->args[i];
		i++;
		j++;
	}
	new_args[j] = NULL;
	return (new_args);
}
