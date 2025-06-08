/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:19 by e                 #+#    #+#             */
/*   Updated: 2025/06/08 19:40:28 by e                ###   ########.fr       */
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

	ow_len = strlen(ow);
	nw_len = strlen(nw);
	r = malloc(strlen(s) + count_occurrences(s, ow) * (nw_len - ow_len) + 1);
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
	return (r);
}
