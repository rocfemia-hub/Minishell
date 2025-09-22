/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 02:24:27 by roo               #+#    #+#             */
/*   Updated: 2025/09/10 20:22:48 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}

int	ft_counterwords(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (!s[i])
			return (word);
		while (s[i] != c && s[i] != '\0')
			i++;
		word++;
	}
	return (word);
}

int	ft_counterletters(char *s, char c, int j)
{
	int	i;

	i = 0;
	while (s[j] && s[j] != c)
	{
		j++;
		i++;
	}
	return (i);
}

char	**get_str(char **p, const char *s, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (words-- != 0)
	{
		while (s[j] && s[j] == c)
			j++;
		p[i] = ft_calloc(ft_counterletters((char *)s, c, j) + 1, sizeof(char));
		if (!p[i])
			return (free_array(p), NULL);
		k = 0;
		while (s[j] && s[j] != c)
			p[i][k++] = s[j++];
		i++;
	}
	return (p);
}

char	**ft_split_mini(char const *s, char c)
{
	char	**p;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_counterwords((char *)s, c);
	p = ft_calloc(words + 1, sizeof(char *));
	if (!p)
		return (0);
	return (get_str(p, s, c, words));
}
