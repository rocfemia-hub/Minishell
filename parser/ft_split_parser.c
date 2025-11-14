/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:18 by roo               #+#    #+#             */
/*   Updated: 2025/11/13 21:50:42 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

static int	skip_quoted_section(char *s, int i)
{
	char	quote;

	quote = s[i++];
	while (s[i] && s[i] != quote)
		i++;
	if (s[i])
		i++;
	return (i);
}

void	count_words_with_quotes(char *s, int i, int *words)
{
	char	c;

	while (s[i])
	{
		i = skip_space(s, i);
		if (!s[i])
			break ;
		(*words)++;
		if (is_redirect(s[i]))
		{
			c = s[i++];
			if (s[i] == c)
				i++;
			continue ;
		}
		while (s[i] && !is_redirect(s[i]) && s[i] != ' ' && s[i] != '\t')
		{
			if (s[i] == '\'' || s[i] == '"')
				i = skip_quoted_section(s, i);
			else
				i++;
		}
	}
}

char	*extract_token(char *s, int *i)
{
	char	c;
	int		start;

	*i = skip_space(s, *i);
	if (!s[*i])
		return (NULL);
	if (is_redirect(s[*i]))
	{
		c = s[*i];
		start = (*i)++;
		if (s[*i] == c)
			(*i)++;
		return (ft_substr(s, start, *i - start));
	}
	start = *i;
	while (s[*i] && !is_redirect(s[*i]) && s[*i] != ' ' && s[*i] != '\t')
	{
		if (s[*i] == '\'' || s[*i] == '"')
			*i = skip_quoted_section(s, *i);
		else
			(*i)++;
	}
	return (ft_substr(s, start, *i - start));
}

char	**ft_split_parser(char const *s)
{
	char	**p;
	int		i;
	int		j;
	int		words;

	if (!s)
		return (NULL);
	words = 0;
	count_words_with_quotes((char *)s, 0, &words);
	p = ft_calloc(words + 1, sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		p[j] = extract_token((char *)s, &i);
		if (!p[j])
			return (free_array(p), NULL);
		j++;
	}
	p[j] = NULL;
	return (p);
}
