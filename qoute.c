/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:21:51 by e                 #+#    #+#             */
/*   Updated: 2025/06/15 16:25:38 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void find_env(char **str, t_env *env_list, int pos)
{
	t_env	*node;
	char	*temp;

	node = env_list;
	while (node)
	{
		temp = ft_strjoin("$", node->key);
		if (!temp)
		{
			node = node->next;
			continue;
		}
		char *new_value = find_and_replace(*str, temp, node->value, pos);
		free(temp);
		if (new_value)
		{
			free(*str);
			*str = new_value;
		}
		node = node->next;
	}
}


int ft_find_len_quote(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (i);
		i++;
	}	
	return (-1);
}

int ft_find_sec_quote(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}	
	return (-1);
}

char *transform_quotes(char *str, t_mini mini)
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
			if(str[d] == '$' && c != '\'')
			{
				if(str[d + 1] == '?')
					str = find_and_replace(str, "$?", ft_itoa(mini.last_status), d);
				find_env(&str, mini.env_list, d);
				de = ft_find_sec_quote(str, d + 1, c);
			}
			if (str[d] == ' ')
				str[d] = TEMP_SPACE_REPLACEMENT;
			if (str[d] == c)
				str[d] = '\x1E';
			if (str[d] == '|')
				str[d] = '\x1D';
			if (str[d] == '>')
				str[d] = '\x1C';
			if (str[d] == '<')
				str[d] = '\x02';
			d++;
		}
	}
	find_env(&str, mini.env_list, 0);
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
	int i;
	int j;

	char *trimmed;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == TEMP_SPACE_REPLACEMENT)
				args[i][j] = ' ';
			if (args[i][j] == '\x1D')
				args[i][j] = '|';
			if (args[i][j] == '\x1C')
				args[i][j] = '>';
			if (args[i][j] == '\x02')
				args[i][j] = '<';
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
