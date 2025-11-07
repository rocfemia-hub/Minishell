/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:46 by roo               #+#    #+#             */
/*   Updated: 2025/11/05 06:54:00 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**realloc_redirect_flags(char **flag)
{
	int		j;
	char	**realloc_matrix;

	j = 0;
	while (flag[j])
		j++;
	realloc_matrix = ft_calloc(j + 2, sizeof(char *));
	if (!realloc_matrix)
		return (NULL);
	j = -1;
	while (flag[++j])
		realloc_matrix[j] = ft_strdup(flag[j]);
	ft_free_free(flag);
	return (realloc_matrix);
}

char	**copy_redirect_matrix(char **args, int start, int end)
{
	int		i;
	int		j;
	char	**new_arg;

	i = 0;
	j = 0;
	while (args[j])
		j++;
	new_arg = ft_calloc(j + 1, sizeof(char *));
	if (!new_arg)
		return (NULL);
	j = 0;
	while (args[j])
	{
		if (j < start || j > end)
		{
			new_arg[i] = ft_strdup(args[j]);
			i++;
		}
		j++;
	}
	ft_free_free(args);
	return (new_arg);
}

char	*expand_redirect_filename(char *file, t_vars *vars)
{
	int		i;
	char	*token;
	char	*result;

	i = 0;
	result = NULL;
	while (file[i])
	{
		if (file[i] == '\'')
			token = handle_single_quotes(file, &i, vars);
		else if (file[i] == '"')
			token = handle_double_quotes(file, &i, vars);
		else if (file[i] == '$')
			token = handle_dollar(file, &i, vars);
		else
			token = handle_plain_text_args(file, &i, vars);
		if (token)
		{
			result = str_append(result, token);
			free(token);
		}
	}
	return (result);
}

void	handle_redirect_array(char ***arr, int *flag, char *file,
		t_com *commands)
{
	char	*expanded;

	if (!*arr)
		*arr = ft_calloc(2, sizeof(char *));
	else
		*arr = realloc_redirect_flags(*arr);
	expanded = expand_redirect_filename(file, commands->vars);
	if (expanded)
		(*arr)[*flag] = expanded;
	else
		(*arr)[*flag] = ft_strdup("");
	(*flag)++;
}

void	fill_type_redirect(t_com *commands, int type)
{
	int	*temp;
	int	i;
	int	size;

	temp = commands->redirects->t_red;
	if (!temp)
	{
		commands->redirects->t_red = ft_calloc(2, sizeof(int));
		commands->redirects->t_red[0] = type;
	}
	else
	{
		size = 0;
		while (temp[size] != 0)
			size++;
		commands->redirects->t_red = ft_calloc(size + 2, sizeof(int));
		i = -1;
		while (++i < size)
			commands->redirects->t_red[i] = temp[i];
		commands->redirects->t_red[size] = type;
		free(temp);
	}
}
