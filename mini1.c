/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:56:08 by roo               #+#    #+#             */
/*   Updated: 2025/06/12 13:56:20 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include "./Helicopter/libft.h"

int main(int argc, char **argv)
{
	char	*line;
	char	**args;
	
	if (!argc && argv)
		return 1;
	while(1)
	{
		line = readline("minishell>");
		if(!line)
			break;
		args = ft_split(line, ' ');
		if(args[0] && ft_strncmp(args[0], "exit", 5) == 0)
			break;
		ft_free_free(args);
		free(line);
	}
}
