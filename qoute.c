/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:21:51 by e                 #+#    #+#             */
/*   Updated: 2025/06/17 19:10:47 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*transform_quotes(char *str, t_mini mini)
{
	char	c;
	int		d;
	int		de;

	d = 0;
	while (str[d] && (ft_strchr(str, '"') || ft_strchr(str, '\'')))
	{
		d = ft_find_len_quote(str, d);
		if (d == -1)
			break ;
		c = str[d];
		de = ft_find_sec_quote(str, d + 1, c);
		if (de == -1)
			break ;
		while (d <= de && str[d])
		{
			if (str[d] == '$' && c != '\'')
			{
				check_question_mark(&str, d, mini);
				de = ft_find_sec_quote(str, d + 1, c);
			}
			swap_characters(str, &d, c);
		}
	}
	return (str);
}

char	*ft_transform_quotes_in_str(char *str, char sign)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] != sign)
			len++;
	}
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != sign)
			new_str[len++] = str[i];
	}
	new_str[len] = '\0';
	return (new_str);
}

void	swap_characters_back(char **args, int i, int j)
{
	if (args[i][j] == TEMP_SPACE_REPLACEMENT)
		args[i][j] = ' ';
	if (args[i][j] == '\x1D')
		args[i][j] = '|';
	if (args[i][j] == '\x1C')
		args[i][j] = '>';
	if (args[i][j] == '\x02')
		args[i][j] = '<';
}

void	transform_spaces(char **args)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			swap_characters_back(args, i, j);
			j++;
		}
		trimmed = ft_transform_quotes_in_str(args[i], '\x1E');
		if (trimmed)
		{
			free(args[i]);
			args[i] = trimmed;
		}
		i++;
	}
}
