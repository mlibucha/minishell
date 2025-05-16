/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:28:12 by e                 #+#    #+#             */
/*   Updated: 2024/12/14 14:06:50 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr++ = (unsigned char)c;
	}
	return (s);
}
