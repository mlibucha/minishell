/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:00:09 by e                 #+#    #+#             */
/*   Updated: 2025/01/01 15:02:21 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_number_length(int number)
{
	unsigned int	len;

	len = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		len += 1;
	while (number != 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	number;
	unsigned int	len;

	len = ft_number_length(n);
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	string[len] = '\0';
	if (n < 0)
	{
		string[0] = '-';
		number = (unsigned int)(-n);
	}
	else
		number = (unsigned int)n;
	if (number == 0)
		string[0] = '0';
	while (number != 0)
	{
		string[len - 1] = (number % 10) + '0';
		number /= 10;
		len--;
	}
	return (string);
}
