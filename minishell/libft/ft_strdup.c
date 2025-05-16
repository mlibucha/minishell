/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:07:43 by e                 #+#    #+#             */
/*   Updated: 2025/05/09 20:09:21 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		a;
	char	*p;

	a = 0;
	if (src == NULL)
		return (NULL);
	p = malloc(ft_strlen(src)+1);
	if (p == NULL)
		return (NULL);
	while (src[a] != '\0')
	{
		p[a] = src[a];
		a++;
	}
	p[a] = '\0';
	return (p);
}
