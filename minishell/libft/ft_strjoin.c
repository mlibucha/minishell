/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:08:56 by e                 #+#    #+#             */
/*   Updated: 2024/12/14 16:02:46 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			a;
	size_t			b;
	char			*c;
	size_t			d;
	char			*start;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	d = a + b;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	c = (char *)malloc(d + 1);
	if (c == NULL)
		return (NULL);
	start = c;
	while (*s1)
		*c++ = *s1++;
	while (*s2)
		*c++ = *s2++;
	*c = '\0';
	return (start);
}
