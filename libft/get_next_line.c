/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:56:42 by roo               #+#    #+#             */
/*   Updated: 2025/03/20 00:19:12 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *buffer)
{
	char	*tmp;
	int		readed;

	readed = 1;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	while (readed > 0 && !ft_strchr_gnl(tmp, '\n'))
	{
		readed = read(fd, tmp, BUFFER_SIZE);
		if (readed > 0)
		{
			tmp[readed] = '\0';
			buffer = ft_strjoin_gnl(buffer, tmp);
		}
	}
	free(tmp);
	if (readed == -1)
		return (ft_free(&buffer));
	return (buffer);
}

char	*get_next_line2(char *buffer, char *next_line)
{
	char	*new_start;
	int		len;

	if (next_line == NULL)
	{
		new_start = NULL;
		return (ft_free(&buffer));
	}
	else
		len = (next_line - buffer) + 1;
	if (!buffer[len])
		return (ft_free(&buffer));
	new_start = ft_substr_gnl(buffer, len, ft_strlen_gnl(buffer) - len);
	ft_free(&buffer);
	if (!new_start)
		return (NULL);
	return (new_start);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*ptr;

	if (fd < 0)
		return (NULL);
	if ((buffer && !ft_strchr_gnl(buffer, '\n')) || !buffer)
		buffer = ft_read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	ptr = ft_strchr_gnl(buffer, '\n');
	line = ft_substr_gnl(buffer, 0, (ptr - buffer) + 1);
	if (!line)
		return (ft_free(&buffer));
	buffer = get_next_line2(buffer, ptr);
	return (line);
}
