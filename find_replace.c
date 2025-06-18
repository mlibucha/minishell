/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:19 by e                 #+#    #+#             */
/*   Updated: 2025/06/18 13:42:15 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	find_suffix_end(const char *s, int pos, int var_len, int s_len)
{
	int	suffix_end;

	suffix_end = pos + var_len;
	while (suffix_end < s_len && is_valid_env_char(s[suffix_end]))
		suffix_end++;
	return (suffix_end);
}

static char	*empty_replacement(char *s, int pos, int suffix_end, int s_len)
{
	int		new_len;
	int		remaining;
	char	*r;

	new_len = s_len - (suffix_end - pos);
	r = malloc(new_len + 1);
	if (!r)
		return (NULL);
	if (pos > 0)
		ft_memcpy(r, s, pos);
	remaining = s_len - suffix_end;
	if (remaining > 0)
		ft_memcpy(r + pos, s + suffix_end, remaining);
	r[pos + remaining] = '\0';
	return (r);
}

char	*handle_normal_replacement(char *s, char *val, int pos, int var_len, int s_len, int val_len)
{
	int		new_len;
	int		remaining;
	char	*r;

	new_len = s_len - var_len + val_len;
	if (new_len < 0)
		return (ft_strdup(s));
	r = malloc(new_len + 1);
	if (!r)
		return (NULL);
	if (pos > 0)
		ft_memcpy(r, s, pos);
	ft_memcpy(r + pos, val, val_len);
	remaining = s_len - (pos + var_len);
	if (remaining > 0)
		ft_memcpy(r + pos + val_len, s + pos + var_len, remaining);
	r[new_len] = '\0';
	return (r);
}

char	*replace(char *s, char *var, char *val, int pos)
{
	int		s_len;
	int		var_len;
	int		val_len;
	int		suffix_end;
	char	*result;

	if (!s || !var || !val)
		return (NULL);
	s_len = ft_strlen(s);
	var_len = ft_strlen(var);
	val_len = ft_strlen(val);
	if (pos < 0 || pos >= s_len)
		return ((s));  // Return a copy instead of original
	if (ft_strncmp(s + pos, var, var_len) != 0)
		return ((s));  // Return a copy instead of original
	if (pos + var_len < s_len && is_valid_env_char(s[pos + var_len]))
	{
		suffix_end = find_suffix_end(s, pos, var_len, s_len);
		result = empty_replacement(s, pos, suffix_end, s_len);
	}
	else
	{
		result = handle_normal_replacement(s, val, pos, var_len, s_len, val_len);
	}
	free(s);  // Free the original string
	return (result);
}
