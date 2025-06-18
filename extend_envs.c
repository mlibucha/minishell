/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:14:16 by emil              #+#    #+#             */
/*   Updated: 2025/06/18 13:46:16 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*replace2(char *s, char *var, char *val, int pos)
{
	int	s_len;
	int	var_len;
	int	val_len;

	if (!s || !var || !val)
		return (NULL);
	s_len = ft_strlen(s);
	var_len = ft_strlen(var);
	val_len = ft_strlen(val);
	if (pos < 0 || pos >= s_len)
		return (ft_strdup(s));
	if (ft_strncmp(s + pos, var, var_len) != 0)
		return (ft_strdup(s));
	return (handle_normal_replacement(s, val, pos, var_len, s_len, val_len));
}

char	*execute_replace(char *input, t_mini *mini, t_env *env_list, int i)
{
	char	*temp;
	char	*new_value;
	t_env	*node;

	node = env_list;
	if (input[i + 1] == '?')
		input = replace2(input, "$?", ft_itoa(mini->last_status), i);
	else
	{
		while (node)
		{
			temp = ft_strjoin("$", node->key);
			if (!temp)
			{
				node = node->next;
				continue ;
			}
			new_value = replace(input, temp, node->value, i);
			free(temp);
			if (new_value)
				input = new_value;
			node = node->next;
		}
	}
	return (input);
}


char	*extend_envs(char *input, t_mini *mini)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
				i++;
		}
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i])
				i++;
		}
		if (input[i] == '$')
			input = execute_replace(input, mini, mini->env_list, i);
	}
	return (input);
}
