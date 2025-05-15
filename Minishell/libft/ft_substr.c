/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:36:15 by e                 #+#    #+#             */
/*   Updated: 2024/12/14 18:21:00 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	sub_len;
	char	*sub;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	sub_len = str_len - start;
	if (sub_len > len)
		sub_len = len;
	sub = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, sub_len + 1);
	return (sub);
}
