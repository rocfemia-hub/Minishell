/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_keep_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:09:38 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 01:20:41 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//archivo nuevo para aux de comillas
static void	flush_buffer(char *arg, int flush, char **args, int *j)
{
	if (flush)
	{
		args[(*j)++] = ft_strdup(arg);
		arg[0] = '\0';
	}
}

static void	add_redir_token(char *line, int *i, char **args, int *j)
{
	if (line[*i + 1] == line[*i])
	{
		args[(*j)++] = ft_strdup((char [3]){line[*i], line[*i], '\0'});
		*i += 2;
	}
	else
	{
		args[(*j)++] = ft_strdup((char [2]){line[*i], '\0'});
		(*i)++;
	}
}
//esta funcion estaba en keep_quotes pero ahora tiene auxiliares y por eso se ha movido
void	process_single_word(char *line, int *i, char **args, int *j)
{
	char	*arg;
	int		k;
	int		is_word; //flag para ver si son o no redirecciones

	arg = ft_calloc(ft_strlen(line) + 3, sizeof(char));
	if (!arg)
		return ;
	k = 0;
	is_word = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
	{
		if (line[*i] == '<' || line[*i] == '>') //se han añadido redirecciones en esta función por eso se ha hecho mas larga
		{
			k = 0;
			flush_buffer(arg, (k > 0 || is_word), args, j);
			add_redir_token(line, i, args, j);
			continue ;
		}
		is_word = 1;
		if (line[*i] == '\'' || line[*i] == '"')
			aux_keep_quotes_args(line, i, &k, &arg);
		else
			arg[k++] = line[(*i)++];
	}
	(flush_buffer(arg, (k > 0 || is_word), args, j), free(arg));
}
