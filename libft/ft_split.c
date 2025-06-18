/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:25:41 by e                 #+#    #+#             */
/*   Updated: 2025/06/18 18:14:19 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	ft_countwords(char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (word);
		}
		i++;
	}
	return (word);
}

static void	ft_strncpy(char *dest, const char *src, int start, int len)
{
	int	i;

	i = 0;
	while (i < len && src[start + i] != '\0')
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
}

static char	*f_allwords(char *str, char c, int *k)
{
	char	*word;
	int		start;
	int		len;

	word = NULL;
	len = 0;
	while (str[*k] != '\0')
	{
		if (str[*k] != c)
		{
			start = *k;
			while (str[*k] != '\0' && str[*k] != c)
			{
				len++;
				(*k)++;
			}
			word = (char *)malloc(sizeof(char) * (len + 1));
			if (!word)
				return (NULL);
			ft_strncpy(word, str, start, len);
			break ;
		}
		(*k)++;
	}
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		pos;

	if (str == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	j = ft_countwords((char *)str, c);
	strs = (char **)malloc(sizeof(char *) * (j + 1));
	if (strs == NULL)
		return (NULL);
	strs[j] = NULL;
	while (i < j)
	{
		strs[i] = f_allwords(((char *)str), c, &pos);
		if (strs[i] == NULL)
		{
			ft_free(strs);
			return (NULL);
		}
		i++;
	}
	return (strs);
}
