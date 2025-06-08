/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:21:51 by e                 #+#    #+#             */
/*   Updated: 2025/06/08 19:34:04 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void find_env(char *str, t_env *env_list)
{
	t_env	*node;

	node = env_list;
	if (ft_strchr(str, '$') == NULL)
		return ;
	while (node)
	{
		if (node->key && node->value)
		{
			char *new_value = find_and_replace(str, node->key, node->value);
			if (new_value)
			{
				free(str);
				str = new_value;
			}
		}
		node = node->next;
	}
	
}

char ft_find_first_quote(char *str)
{
	char first_quote;
	int i;

	i = 0;
	first_quote = '"';
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			first_quote = str[i];
			return (first_quote);
		}
		i++;
	}	
	return (first_quote);
}

char *transform_quotes(char *str, t_env *env_list)
{
	char *first_quote;
	char *last_quote;
	char *p;
	char c;

	c = ft_find_first_quote(str);
	if (c != '\'')
		find_env(str, env_list);
	first_quote = ft_strchr(str, c);
	last_quote = ft_strrchr(str, c);
	if (first_quote == NULL || last_quote == NULL || first_quote == last_quote)
		return (str);
	*first_quote = '\x1E';
	*last_quote = '\x1E';
	p = first_quote + 1;
	while (p < last_quote)
	{
		if (*p == ' ')
		{
			*p = TEMP_SPACE_REPLACEMENT;
		}
		p++;
	}
	return (str);
}


char *ft_transform_quotes_in_str(char *str, char sign)
{
	char *new_str;
	int len;
	int i;

	len = 0;
	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if(str[i] != sign)
			len++;
	}
	new_str = malloc(sizeof(char *) * (len + 1));
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

void transform_spaces(char **args)
{
	int i = 0;
	int j;

	char *trimmed;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == TEMP_SPACE_REPLACEMENT)
			{
				args[i][j] = ' ';
			}
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
