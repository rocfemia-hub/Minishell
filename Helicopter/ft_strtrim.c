/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocfemia <rocfemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:28:13 by roo               #+#    #+#             */
/*   Updated: 2024/10/12 08:01:41 by rocfemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_first(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s1[i] != '\0' && set[j] != '\0')
	{
		if (s1[i] != set[j])
		{
			j++;
			if (set[j] == '\0')
				break ;
		}
		else
		{
			k++;
			i++;
			j = 0;
		}
	}
	return (k);
}

static size_t	ft_last(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s1);
	while (i < len && set[j] != '\0')
	{
		if (s1[len - i - 1] != set[j])
		{
			j++;
			if (set[j] == '\0')
				break ;
		}
		else
		{
			k++;
			i++;
			j = 0;
		}
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*str;
	size_t	not1;
	size_t	not2;
	size_t	nlen;

	i = -1;
	if (!s1 || !set)
		return (NULL);
	not1 = ft_first(s1, set);
	not2 = ft_last(s1, set);
	nlen = ft_strlen(s1) - (not1 + not2);
	if (ft_strlen(s1) < not1 + not2)
		nlen = 0;
	str = (char *)malloc(sizeof(char) * (nlen + 1));
	if (!str)
		return (NULL);
	while (++i < nlen)
		str[i] = s1[not1 + i];
	str[i] = '\0';
	return (str);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strtrim("jaaeijjPepinojjj", "jaei"));
	return(0);
}*/