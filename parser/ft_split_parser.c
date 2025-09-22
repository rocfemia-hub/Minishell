#include "../minishell.h"

void free_array_parser(char **p)
{
    int i;

    i = -1;
    while (p[++i])
        free(p[i]);
    free(p);
}

int counter_words(char *s)
{
    int i;
    int word;

    i = 0;
    word = 0;
    while (s[i] != '\0')
    {
        while (s[i] == 32 && s[i] != '\0')
            i++;
        if (!s[i])
            return (word);
        while (s[i] != 32 && s[i] != '\0')
            i++;
        word++;
    }
    return (word);
}

int counter_letters(char *s, int j)
{
    int letter;

    letter = 0;
    while (s[j] && s[j] == 32)
    {
        j++;
        letter++;
    }
    while (s[j] && s[j] != 32)
    {
        j++;
        letter++;
    }
    while (s[j] && s[j] == 32)
    {
        j++;
        letter++;
    }
    return (letter);
}

char **get_str_parser(char **p, const char *s, int words)
{
    int i;
    int j;
    int k;
    int letter;

    i = 0;
    j = 0;
    while (words != 0)
    {
        letter = counter_letters((char *)s, j);
        p[i] = ft_calloc(letter + 1, sizeof(char));
        if (!p[i])
            return (free_array_parser(p), NULL);
        k = 0;
        while (s[j] && k < letter)
            p[i][k++] = s[j++];
        i++;
        words--;
    }
    return (p);
}

char **ft_split_parser(char const *s)
{
    char **p;
    int words;

    if (s == NULL)
        return (NULL);
    words = counter_words((char *)s);
    p = ft_calloc(words + 1, sizeof(char *));
    if (!p)
        return (0);
    return (get_str_parser(p, s, words));
}
