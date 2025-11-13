/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:52:17 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 03:43:04 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//este archivo es nuevo, gestiona la virgulilla entera
static char	*expand_tilde(const char *word, t_vars *vars)
{
	t_env	*home;
	char	*path;
	//esta funcion sustituye virgulilla por el path del home
	if (!word || word[0] != '~')
		return (ft_strdup(word));
	if (word[1] == '/' || word[1] == '\0')
	{
		home = find_env_var(vars, "HOME");
		if (!home || !home->env_inf)
			return (ft_strdup(word));
		path = ft_strjoin(home->env_inf, word + 1);
		if (path)
			return (path);
		return (ft_strdup(word));
	}
	return (ft_strdup(word));
}

char	*handle_tilde(char *line, int *i, t_vars *vars)
{
	int		start;
	char	*word;
	char	*expanded;
	//esta funcion busca la virgulilla en cmds y args
	start = *i;
	(*i)++;
	while (line[*i] && !ft_strchr(" \t\n'$\"", line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
	expanded = expand_tilde(word, vars);
	free(word);
	return (expanded);
}
