/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:18:44 by e                 #+#    #+#             */
/*   Updated: 2024/12/14 18:34:25 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *c)
{
	int	a;
	int	j;
	int	res;
	int	si;

	a = 0;
	res = 0;
	j = 0;
	si = 1;
	while (c[a] == ' ' || c[a] == '\t' || c[a] == '\n'
		||c[a] == '\v' || c[a] == '\f' || c[a] == '\r')
		a++;
	while (c[a] == '-' || c[a] == '+')
	{
		if (c[a] == '-')
			si = si * -1;
		a++;
		j++;
	}
	while (c[a] >= '0' && c[a] <= '9')
		res = res * 10 + (c[a++] - '0');
	if (j > 1)
		return (0);
	return (res * si);
}
