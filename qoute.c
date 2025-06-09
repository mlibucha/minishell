/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:21:51 by e                 #+#    #+#             */
/*   Updated: 2025/06/09 20:03:49 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


// static void handle_unquoted_vars(char **str_ptr, t_env *env_list)
// {
// 	char *str = *str_ptr;
// 	size_t pos = 0;
// 	bool expanded;

// 	if (!str || !env_list)
// 		return ;
// 	do
// 	{
// 		expanded = false;
// 		while (str[pos])
// 		{
// 			if (str[pos] == '$')
// 			{
// 				char *single_quote = ft_strchr(str, '\'');
// 				if (single_quote && &str[pos] > single_quote &&
// 					ft_strchr(single_quote + 1, '\''))
// 				{
// 					pos++;
// 					continue ;
// 				}
// 				size_t old_pos = pos;
// 				char *old_str = str;
// 				int old_len = ft_strlen(str);
// 				char *var_start = &str[pos];
// 				char *var_end = var_start + 1;
// 				while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
// 					var_end++;
// 				expand_env_vars(str_ptr, env_list, var_start, var_end);
// 				str = *str_ptr;
// 				if (str != old_str || ft_strlen(str) != old_len)
// 				{
// 					expanded = true;
// 					pos = 0;
// 					break ;
// 				}
// 				else
// 					pos = old_pos + 1; 
// 			}
// 			else
// 				pos++;
// 		}
// 	}
// 	while (expanded);
// }


#include "mini.h"

static bool	is_in_single_quotes(char *str, char *pos)
{
	char	*sq_start;

	sq_start = ft_strchr(str, '\'');
	return (sq_start && pos > sq_start && ft_strchr(sq_start + 1, '\''));
}

static char	*find_var_end(char *var_start)
{
	char	*var_end;

	var_end = var_start + 1;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	return (var_end);
}

static void	process_var_expansion(char **str_ptr, t_env *env_list,
				size_t *pos, bool *expanded)
{
	char	*str;
	size_t	old_pos;
	char	*old_str;
	int		old_len;
	char	*var_end;

	str = *str_ptr;
	old_pos = *pos;
	old_str = str;
	old_len = ft_strlen(str);
	var_end = find_var_end(&str[old_pos]);
	expand_env_vars(str_ptr, env_list, &str[old_pos], var_end);
	str = *str_ptr;
	if (str != old_str || (int)ft_strlen(str) != old_len)
	{
		*expanded = true;
		*pos = 0;
	}
	else
		*pos = old_pos + 1;
}

void		handle_unquoted_vars(char **str_ptr, t_env *env_list)
{
	char	*str;
	size_t	pos;
	bool	expanded;

	if (!*str_ptr || !env_list)
		return ;
	str = *str_ptr;
	pos = 0;
	expanded = true;
	while (expanded && str[pos])
	{
		expanded = false;
		if (str[pos] == '$' && !is_in_single_quotes(str, &str[pos]))
			process_var_expansion(str_ptr, env_list, &pos, &expanded);
		else
			pos++;
	}
}

static void handle_single_quotes(char **str_ptr)
{
	char *start;
	char *end;
	char *str = *str_ptr;

	while ((start = ft_strchr(str, '\'')))
	{
		end = ft_strchr(start + 1, '\'');
		if (!end)
			break;
		*start = '\x1E';
		*end = '\x1E';
		char *p = start + 1;
		while (p < end)
		{
			if (*p == ' ')
				*p = TEMP_SPACE_REPLACEMENT;
			p++;
		}
		str = end + 1;
	}
}

static void handle_double_quotes(char **str_ptr, t_env *env_list)
{
	char *start;
	char *end;
	char *str;

	str = *str_ptr;
	while ((start = ft_strchr(str, '"')))
	{
		end = ft_strchr(start + 1, '"');
		if (!end)
			break;
		*start = '\x1E';
		*end = '\x1E';
		char *p = start + 1;
		while (p < end)
		{
			if (*p == ' ')
				*p = TEMP_SPACE_REPLACEMENT;
			p++;
		}
		expand_env_vars(str_ptr, env_list, start + 1, end - 1);
		str = *str_ptr;
	}
}

char *transform_quotes(char *str, t_env *env_list)
{
	if (!str)
		return (NULL);
	printf("Transforming quotes in string: %s\n", str);
	handle_unquoted_vars(&str, env_list);
	handle_single_quotes(&str);
	handle_double_quotes(&str, env_list);
	return (str);
}

char *ft_transform_quotes_in_str(char *str, char sign)
{
	char *new_str;
	int len = 0;
	int i = -1;

	if (!str)
		return (NULL);
	while (str[++i])
		if (str[i] != sign)
			len++;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	len = 0;
	i = -1;
	while (str[++i])
		if (str[i] != sign)
			new_str[len++] = str[i];
	new_str[len] = '\0';
	return (new_str);
}
