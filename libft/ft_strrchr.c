/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:22:20 by e                 #+#    #+#             */
/*   Updated: 2024/12/14 18:18:21 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;
	const char	*end;

	len = ft_strlen(s);
	end = s + len - 1;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (len--)
	{
		if (*end == (char)c)
			return ((char *)end);
		end--;
	}
	return (0);
}
