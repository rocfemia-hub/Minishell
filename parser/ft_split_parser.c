/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:37:18 by roo               #+#    #+#             */
/*   Updated: 2025/09/25 17:37:20 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_array_parser(char **p)
{
    int i;

    i = -1;
    while (p && p[++i])
        free(p[i]);
    free(p);
}

int skip_space(char *s, int i)
{
    while (s[i] == ' ')
        i++;
    return (i);
}

int count_words_with_quotes(char *s)
{
    int i;
    int words;
    char quote;

    i = 0;
    words = 0;
    while (s[i])
    {
        i = skip_space(s, i);
        if (!s[i])
            break;
        words++;
        if (s[i] == '\'' || s[i] == '"')
        {
            quote = s[i++];
            while (s[i] && s[i] != quote)
                i++;
            if (s[i])
                i++;
        }
        else
            while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
                i++;
    }
    return (words);
}

char *extract_token(char *s, int *i)
{
    int start;
    char quote;

    *i = skip_space(s, *i);
    if (!s[*i])
        return (NULL);

    start = *i;
    if (s[*i] == '\'' || s[*i] == '"')
    {
        quote = s[*i];
        (*i)++;
        while (s[*i] && s[*i] != quote)
            (*i)++;
        if (s[*i])
            (*i)++; // saltamos la comilla de cierre
    }
    else
    {
        while (s[*i] && s[*i] != ' ' && s[*i] != '\'' && s[*i] != '"')
            (*i)++;
    }
    return (ft_substr(s, start, *i - start));
}

char **ft_split_parser(char const *s)
{
    char **p;
    int i;
    int j;
    int words;

    if (!s)
        return (NULL);
    words = count_words_with_quotes((char *)s);
    p = ft_calloc(words + 1, sizeof(char *));
    if (!p)
        return (NULL);
    i = 0;
    j = 0;
    while (j < words)
    {
        p[j] = extract_token((char *)s, &i);
        if (!p[j])
            return (free_array_parser(p), NULL);
        j++;
    }
    p[j] = NULL;
    return (p);
}
