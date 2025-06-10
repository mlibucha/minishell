/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:21:51 by e                 #+#    #+#             */
/*   Updated: 2025/06/10 18:23:16 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void find_env(char **str, t_env *env_list)
{
	t_env	*node;
	char	*temp;

	node = env_list;
	int i = 0;
	while (str[i] && str[i][0] == '$')
	{
		i++;
	}
	while (node)
	{
		temp = ft_strjoin("$", node->key);
		char *new_value = find_and_replace(*str, temp, node->value);
		if (new_value)
		{
			free(*str);
			*str = new_value;
		}
		node = node->next;
	}
}

char ft_find_first_quote(char *str, int i)
{
	char first_quote;

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

int ft_find_len_quote(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			return (i);
		}
		i++;
	}	
	return (-1);
}

int ft_find_sec_quote(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
		{
			return (i);
		}
		i++;
	}	
	return (-1);
}

char *transform_quotes(char *str, t_env *env_list)
{
	char c;
	int d;
	int de;

	d = 0;
	while (str[d] && (ft_strchr(str, '"') || ft_strchr(str, '\'')))
	{
		d = ft_find_len_quote(str, d);
		if (d == -1)
			break;
		c = str[d];
		de = ft_find_sec_quote(str, d + 1, c);
		if (de == -1)
			break;
		while (d <= de && str[d])
		{
			if (str[d] == ' ')
			{
				str[d] = TEMP_SPACE_REPLACEMENT;
			}
			if (str[d] == c)
			{
				str[d] = '\x1E';
			}
			d++;
		}
		printf("transformed string: %s\n", str);
	}
	find_env(&str, env_list);
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