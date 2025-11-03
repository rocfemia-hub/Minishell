/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_matrix                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:39:18 by roo               #+#    #+#             */
/*   Updated: 2025/11/03 20:40:17 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**malloc_matrix(char **matrix)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_calloc((matrix_len(matrix)) + 1, sizeof(char *));
	while (matrix && matrix[i])
	{
		result[i] = ft_strdup(matrix[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
