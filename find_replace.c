/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:19 by e                 #+#    #+#             */
/*   Updated: 2025/06/09 18:00:44 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	count_occurrences(const char *s, const char *ow)
{
	char	*p;
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while ((p = strstr(s + i, ow)))
	{
		cnt++;
		i = p - s + strlen(ow);
	}
	return (cnt);
}

char	*find_and_replace(const char *s, const char *ow, const char *nw)
{
	char	*r;
	int		i;
	int		ow_len;
	int		nw_len;

	ow_len = ft_strlen(ow);
	nw_len = ft_strlen(nw);
	r = malloc(ft_strlen(s) + count_occurrences(s, ow) * (nw_len - ow_len) + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (ft_strnstr(s, ow, ft_strlen(ow)) == s)
		{
			ft_strlcpy(r + i, nw, nw_len + 1);
			i += nw_len;
			s += ow_len;
		}
		else
			r[i++] = *s++;
	}
	r[i] = '\0';
	printf("find_and_replace: %s\n", r);
	return (r);
}


static char *replace_env_var(char *current, char **start_ptr, char **end_ptr, t_env *env_list)
{
	char *var_start = ft_strchr(*start_ptr, '$');
	char *var_end = var_start + 1;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	char *var_name = ft_substr(var_start + 1, 0, var_end - (var_start + 1));
	if (!var_name)
		return (NULL);
	char *temp = ft_strjoin("$", var_name);
	t_env *node = env_list;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, var_name))
		{
			char *new_str = find_and_replace(current, temp, node->value);
			//free(temp);
			free(var_name);
			if (!new_str)
				return (NULL);
			*start_ptr = new_str + (*start_ptr - current);
			*end_ptr = new_str + (*end_ptr - current) + (ft_strlen(node->value) - ft_strlen(temp));
			return (new_str);
		}
		node = node->next;
	}
	*start_ptr = var_end;
	return (free(temp), free(var_name), current);
}

void expand_env_vars(char **str_ptr, t_env *env_list, char *start, char *end)
{
	char *current = *str_ptr;
	char *var_start = ft_strchr(start, '$');
	char *prev_str = NULL;

	while (var_start && var_start < end)
	{
		if (var_start[1] == '\0' || var_start[1] == ' ')
			break ;
		prev_str = current;
		current = replace_env_var(current, &start, &end, env_list);
		if (!current)
			break ;
		if (current == prev_str)
		{
			start = var_start + 1;
			var_start = ft_strchr(start, '$');
			break ;
		}
		*str_ptr = current;
		var_start = ft_strchr(start, '$');
		end = current + ft_strlen(current);
	}
}
void transform_spaces(char **args)
{
	int i;
	char *trimmed;

	i  = 0;
	while (args[i])
	{
		int j = 0;
		while (args[i][j])
		{
			if (args[i][j] == TEMP_SPACE_REPLACEMENT)
				args[i][j] = ' ';
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
