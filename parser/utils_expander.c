/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:56 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:54:08 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*handle_dollar_in_quotes(char *line, int *k, int *start, t_vars *vars)
{
	char	*tmp;
	char	*token;

	token = NULL;
	if (*k > *start)
	{
		tmp = ft_substr(line, *start, *k - *start);
		token = str_append(token, tmp);
		free(tmp);
	}
	*start = *k;
	token = expand_var_in_quotes_args(line, k, token, vars);
	*start = *k;
	return (token);
}

char	*process_inside_double_quotes(char *line, int start, int end,
		t_vars *vars)
{
	int		k;
	char	*token;
	char	*tmp;

	token = NULL;
	k = start;
	while (k < end)
	{
		if (line[k] == '$')
			token = str_append(token, handle_dollar_in_quotes(line, &k,
						&start, vars));
		else
			k++;
	}
	if (start < end)
	{
		tmp = ft_substr(line, start, end - start);
		token = str_append(token, tmp);
		free(tmp);
	}
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
