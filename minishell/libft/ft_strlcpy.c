/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:19:42 by e                 #+#    #+#             */
/*   Updated: 2024/12/14 14:25:15 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*s;
	size_t		n;

	s = src;
	n = size;
	if (n)
	{
		while (--n)
		{
			*dest = *s;
			if (*s == '\0')
				break ;
			dest++;
			s++;
		}
		if (size > 0)
			*dest = '\0';
	}
	while (*s)
		s++;
	return (s - src);
}
