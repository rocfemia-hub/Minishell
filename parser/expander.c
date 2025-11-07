/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:30 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 07:01:28 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_inter(t_vars *vars)
{
	char	*nbr;

	nbr = ft_itoa(vars->exit_status);
	return (nbr);
}

char	*get_env_var(t_vars *vars, char *var)
{
	t_env	*node;

	node = find_env_var(vars, var);
	if (node != NULL)
		return (node->env_inf);
	else
		return ("");
}

char	*handle_single_quotes(char *line, int *i, t_vars *vars)
{
	int		start;
	char	*token;
	int		len;

	if (!vars)
		return (NULL);
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	len = *i - start;
	if (len == 0)
		token = ft_strdup("");
	else
		token = ft_substr(line, start, len);
	if (line[*i] == '\'')
		(*i)++;
	return (token);
}

char	*aux_expand_var_in_quotes_args(char *token, t_vars *vars, int *k,
		int *start)
{
	char	*value;
	int		vstart;

	vstart = *k + 1;
	value = ft_itoa(vars->exit_status);
	token = str_append(token, value);
	free(value);
	*k = vstart + 1;
	*start = *k;
	return (token);
}

char	*handle_invalid_var(char *token)
{
	token = str_append(token, "$");
	return (token);
}
