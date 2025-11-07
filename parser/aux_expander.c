/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:52 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:59:31 by roo              ###   ########.fr       */
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

static char	*handle_var_expansion(t_vars *vars, char *line, int start,
		int *vlen)
{
	char	*varname;
	char	*value;
	char	*token;

	varname = extract_varname(line, start, vlen);
	value = get_env_var(vars, varname);
	free(varname);
	token = ft_strdup(value);
	return (token);
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
