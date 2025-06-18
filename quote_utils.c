/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 06:05:14 by emil              #+#    #+#             */
/*   Updated: 2025/06/18 13:47:17 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	find_env(char **str, t_env *env_list, int pos)
{
	t_env	*node;
	char	*temp;
	char	*new_value;

	node = env_list;
	while (node)
	{
		temp = ft_strjoin("$", node->key);
		if (!temp)
		{
			node = node->next;
			continue ;
		}
		new_value = replace(*str, temp, node->value, pos);
		free(temp);
		if (new_value)
		{
			*str = new_value;
		}
		node = node->next;
	}
}

int	ft_find_len_quote(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_find_sec_quote(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	swap_characters(char *str, int *d, char c)
{
	if (str[*d] == ' ')
		str[*d] = TEMP_SPACE_REPLACEMENT;
	if (str[*d] == c)
		str[*d] = '\x1E';
	if (str[*d] == '|')
		str[*d] = '\x1D';
	if (str[*d] == '>')
		str[*d] = '\x1C';
	if (str[*d] == '<')
		str[*d] = '\x02';
	(*d)++;
}

void	check_question_mark(char **str, int d, t_mini mini)
{
	if ((*str)[d + 1] == '?')
		*str = replace(*str, "$?", ft_itoa(mini.last_status), d);
	find_env(str, mini.env_list, d);
}
