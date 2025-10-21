/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:54:55 by roo               #+#    #+#             */
/*   Updated: 2025/10/21 20:18:33 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_num(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

static int	ft_lett_words(const char *s, char c, int k)
{
	int	lett_len;
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			lett_len = 0;
			while (s[i] != c && s[i] != '\0')
			{
				lett_len++;
				i++;
			}
			if (k == 0)
				return (lett_len);
			k--;
		}
		i++;
	}
	return (0);
}

void	ft_free_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static char	**ft_split2(const char *s, char c, char **matrix)
{
	int	i;
	int	j;
	int	word_len;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			word_len = ft_lett_words(s, c, k);
			matrix[k] = (char *)malloc((word_len + 1) * sizeof(char));
			if (!matrix[k])
				return (ft_free_free(matrix), NULL);
			j = 0;
			while (s[i] != '\0' && s[i] != c)
				matrix[k][j++] = s[i++];
			matrix[k][j] = '\0';
			k++;
		}
	}
	return (matrix[k] = NULL, matrix);
}

char	**ft_split(const char *s, char c)
{
	size_t	words;
	char	**matrix;

	words = ft_words_num((char *)s, c);
	matrix = (char **)malloc((words + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix = ft_split2(s, c, matrix);
	return (matrix);
}
/*#include <stdio.h>

int	main(void)
{
	char	s[] = " Me  gustan las  patatas ";
	char	c;
	int		i;
	char	**p;

	c = ' ';
	i = 0;
	p = ft_split(s, c);
	while (p[i])
	{
		printf("%s\n", p[i]);
		i++;
	}
	// printf("%i\n", ft_lett_words(" Me  gustan las  patatas ", ' '));
	return (0);
}*/
/*#include <stdio.h>
int	main(void)
{
	printf("%i\n", ft_words_num(" Me  gustan las  patatas ", ' '));
	return(0);
} */
// malloc(ft_words_num() * (char *))
// char **matrix;
/*#include <stdio.h>
int	main() //ORIGINAL
{
	char matrix[][] = "Me gustan las patatas"
	printf("%s\n", ft_split("Me  gustan las patatas", ' '));
}*/

/*int main(void)
{
	char	s[] = "Pat ata as";
	char	c = ' ';
	char	**str;

	str = ft_split(s, c);
	for(int i = 0; i < 2; i++)
		printf("%s\n", str[i]);
} */