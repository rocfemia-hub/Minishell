/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 03:47:09 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_var_expansion(t_vars *vars, char *line, int start,
		int *vlen)
{
	char	*varname;
	char	*value;

	varname = extract_varname(line, start, vlen);
	value = get_env_var(vars, varname);
	free(varname);
	if (ft_strlen(value) == 0)
		return (NULL);
	return (ft_strdup(value));
}

char	*aux_handle_dollar(int *i, int start)
{
	char	*token;

	token = ft_strdup("");
	*i = start;
	return (token);
}

char	*handle_dollar(char *line, int *i, t_vars *vars)
{
	int		start;
	int		vlen;
	char	*token;

	token = NULL;
	start = *i + 1;
	if (line[start] == '?')
	{
		token = handle_inter(vars);
		*i = start + 1;
	}
	else if (ft_isalnum((unsigned char)line[start]) || line[start] == '_')
	{
		token = handle_var_expansion(vars, line, start, &vlen);
		*i = start + vlen;
	}
	else if (line[start] == '"' || line[start] == '\'')
		token = aux_handle_dollar(i, start);
	else
	{
		token = ft_strdup("$");
		*i = start;
	}
	return (token);
}

char	*extract_and_expand_var(char *line, int vstart, int *vlen,
		t_vars *vars)
{
	char	*varname;
	char	*value;

	*vlen = 0;
	while (line[vstart + *vlen] && (ft_isalnum((unsigned char)line[vstart
					+ *vlen]) || line[vstart + *vlen] == '_'))
		(*vlen)++;
	varname = ft_substr(line, vstart, *vlen);
	value = get_env_var(vars, varname);
	free(varname);
	return (value);
}

void	add_split_args(char **token_args, int *j, char *accumulated)
{
	char	**split;
	int		k;

	split = ft_split_parser(accumulated);
	if (!split)
		return ;
	k = -1;
	while (split[++k])
		token_args[(*j)++] = split[k];
	free(split);
}
