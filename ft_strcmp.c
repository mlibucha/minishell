/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:58:59 by estolarc          #+#    #+#             */
/*   Updated: 2025/05/29 17:01:04 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;

	a = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[a] != '\0' || s2[a] != '\0')
	{
		if (s1[a] != s2[a])
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		a++;
	}
	return (0);
}
