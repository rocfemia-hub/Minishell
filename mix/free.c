/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:17:12 by roo               #+#    #+#             */
/*   Updated: 2025/11/21 14:17:50 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static void	free_t_env_list(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		temp = list->next;
		if (list->env_inf)
			free(list->env_inf);
		if (list->env_name)
			free(list->env_name);
		free(list);
		list = temp;
	}
}

static void	free_t_vars_list(t_vars *list)
{
	if (list->env_list)
		free_t_env_list(list->env_list);
}*/

static void	free_t_red_list(t_red *list)
{
	if (!list)
		return ;
	if (list->input_file)
		ft_free_free(list->input_file);
	if (list->output_file)
		ft_free_free(list->output_file);
	if (list->append_file)
		ft_free_free(list->append_file);
	if (list->heredoc_file)
		free(list->heredoc_file);
	if (list->delimiter)
		free(list->delimiter);
	if (list->t_red)
		free(list->t_red);
	free(list);
}

void	free_t_com_list(t_com *list)
{
	t_com	*temp;

	while (list)
	{
		temp = list->next;
		if (list->command)
			free(list->command);
		if (list->command_arg)
			ft_free_free(list->command_arg);
		if (list->args)
			ft_free_free(list->args);
		if (list->path_command)
			free(list->path_command);
		if (list->error)
			free(list->error);
		if (list->redirects)
			free_t_red_list(list->redirects);
		free(list);
		list = temp;
	}
}
