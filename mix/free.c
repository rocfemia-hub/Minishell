/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:17:12 by roo               #+#    #+#             */
/*   Updated: 2025/10/05 19:37:21 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_t_env_list(t_env *list)
{
    while(list)
    {
        free(list->env_inf);
        free(list->env_name);
        list = list->next;
    }
}
void free_t_vars_list(t_vars *list)
{
    if (list->argv)
        ft_free_free(list->argv);
    if (list->env)
        ft_free_free(list->argv);
    if (list->env_list)
        free_t_env_list(list->env_list);
}

void free_t_red_list(t_red *list)
{
    if (list->input_file)
        ft_free_free(list->input_file);
    if (list->output_file)
        ft_free_free(list->output_file);
    if (list->append_file)
        ft_free_free(list->append_file);
    if (list->delimiter)
        free(list->delimiter);
}

void free_t_com_list(t_com *list)
{
    if(list->command)
        free(list->command);
    if(list->command_arg)
        free(list->command_arg);
    if(list->args)
        ft_free_free(list->args);
    if(list->path_command)
        free(list->path_command);
    if (list->error)
        free(list->error);
    if(list->redirects)
        free_t_red_list(list->redirects);
    if (list->vars)
        free_t_vars_list(list->vars);
}       