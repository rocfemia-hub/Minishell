/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:56 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 02:53:18 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_varname(char *line, int start, int *vlen)
{
	char	*varname;

	*vlen = 0;
	if (line[start] && (ft_isalpha((unsigned char)line[start])
			|| line[start] == '_'))
	{
		(*vlen)++;
		while (line[start + *vlen] && (ft_isalnum((unsigned char)line[start
						+ *vlen]) || line[start + *vlen] == '_'))
			(*vlen)++;
	}
	else if (line[start] && ft_isdigit((unsigned char)line[start]))
		(*vlen) = 1;
	varname = ft_substr(line, start, *vlen);
	return (varname);
}

char	*expand_var_in_quotes_args(char *line, int *k, char *token,
		t_vars *vars)
{
	int		vstart;
	int		vlen;
	char	*value;
	int		start;

	start = *k;
	vstart = *k + 1;
	if (line[vstart] == '?')
		return (aux_expand_var_in_quotes_args(token, vars, k, &start));
	if (!line[vstart] || !(ft_isalnum((unsigned char)line[vstart])
			|| line[vstart] == '_'))
	{
		*k = vstart;
		return (handle_invalid_var(token));
	}
	value = extract_and_expand_var(line, vstart, &vlen, vars);
	token = str_append(token, value);
	*k = vstart + vlen;
	return (token);
}

static char	*append_and_free(char *token, char *tmp)
{
	token = str_append(token, tmp);
	free(tmp);
	return (token);
}

char	*process_inside_double_quotes(char *line, int start, int end,
		t_vars *vars)
{
	int		k;
	char	*token;

	token = NULL;
	k = start;
	while (k < end)
	{
		if (line[k] == '$')
			token = append_and_free(token, handle_dollar_in_quotes(line, &k,
						&start, vars));
		else
			k++;
	}
	if (start < end)
		token = append_and_free(token, ft_substr(line, start, end - start));
	if (!token)
		token = ft_strdup("");
	return (token);
}

char	*handle_double_quotes(char *line, int *i, t_vars *vars)
{
	int		end;
	char	*token;

	(*i)++;
	end = *i;
	while (line[end] && line[end] != '"')
		end++;
	token = process_inside_double_quotes(line, *i, end, vars);
	if (line[end] == '"')
		end++;
	*i = end;
	return (token);
}
