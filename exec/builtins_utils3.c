/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:36:34 by roo               #+#    #+#             */
/*   Updated: 2025/11/11 18:30:49 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	list_size(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**list_to_env(t_env *env_list)
{
	char	**env;
	char	*tmp;
	int		i;

	i = 0;
	env = ft_calloc(list_size(env_list) + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		tmp = ft_strjoin(env_list->env_name, "=");
		if (env_list->env_inf)
			env[i++] = ft_strjoin(tmp, env_list->env_inf);
		free(tmp);
		env_list = env_list->next;
	}
	return (env);
}

void	env_to_list(t_vars *vars, char **env)
{
	t_env	*new_var;
	t_env	*env_list;
	int		i;

	i = 0;
	vars->env_list = NULL;
	while (env[i])
	{
		new_var = create_env_list(env[i]);
		if (!vars->env_list)
			vars->env_list = new_var;
		else
		{
			env_list = vars->env_list;
			while (env_list->next)
				env_list = env_list->next;
			env_list->next = new_var;
		}
		i++;
	}
}

void	increment_shlvl(t_vars *vars)
{
	t_env	*shlvl;
	char	*new;
	char	*joined;
	int		current;

	shlvl = find_env_var(vars, "SHLVL");
	if (shlvl)
	{
		current = ft_atoi(shlvl->env_inf);
		current++;
	}
	else
		current = 1;
	new = ft_itoa(current);
	joined = ft_strjoin("SHLVL=", new);
	add_update_env_var(vars, joined, 0);
	free(joined);
	free(new);
}

int	line_break(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (0);
	while (line && line[i] == 32)
		i++;
	if (!line[i])
		return (0);
	else
		return (1);
}
