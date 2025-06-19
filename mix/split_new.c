#include "../minishell.h"

void	free_array(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}

int	ft_counterwords(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == '|' || s[i] == '<' || s[i] == '>' || s[i] == ' ') && s[i] != '\0')
			i++;
		if (!s[i])
			return (word);
		while (!(s[i] == '|' || s[i] == '<' || s[i] == '>' || s[i] == ' ') && s[i] != '\0')
			i++;
		word++;
	}
	return (word);
}

int	ft_counterletters(char *s, int j)
{
	int	len = 0;

	while (s[j] && (s[j] == '|' || s[j] == '<' || s[j] == '>' || s[j] == ' '))
		j++;
	while (s[j] && !(s[j] == '|' || s[j] == '<' || s[j] == '>' || s[j] == ' '))
	{
		len++;
		j++;
	}
	return (len);
}


char	**get_str(char **p, const char *s, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (words-- != 0)
	{
		while (s[j] && (s[j] == '|' || s[j] == '<' || s[j] == '>' || s[j] == ' '))
			j++;
		p[i] = ft_calloc(ft_counterletters((char *)s, j) + 1, sizeof(char));
		if (!p[i])
			return (free_array(p), NULL);
		k = 0;
		while (s[j] && !(s[j] == '|' || s[j] == '<' || s[j] == '>' || s[j] == ' '))
			p[i][k++] = s[j++];
		i++;
	}
	return (p);
}

char	**ft_split_new(char const *s)
{
	char	**p;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_counterwords((char *)s);
	p = ft_calloc(words + 1, sizeof(char *));
	if (!p)
		return (0);
	return (get_str(p, s, words));
}
