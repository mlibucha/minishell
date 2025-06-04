/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:06:38 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/02 16:07:09 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

long	ft_atol(char *str)
{
	long int	number;
	int			sign;
	int			i;

	sign = 1;
	i = -1;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (LONG_MIN);
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	number = 0;
	while (str[++i])
		number = number * 10 + (str[i] - '0');
	return (number * sign);
}

int	ft_str_is_numeric(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_long(char *number)
{
	if (number == NULL)
		return (1);
	if (number[0] == '-' || number[0] == '+')
	{
		if (ft_strlen(number) > 20 || !ft_str_is_numeric(number, 1))
			return (0);
		if (ft_strlen(number) == 20 && ft_strcmp(number, "-9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(number) > 19 || !ft_str_is_numeric(number, 0))
			return (0);
		if (ft_strlen(number) == 19 && ft_strcmp(number, "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

int	mini_exit(t_cmd *cmd, t_mini *mini, int a)
{
	long int	status;

	status = 0;
	if (a != 0)
		return (1);
	if (!is_long(cmd->args[1]))
	{
		ft_putendl_fd("exit", 1);
		free_values(mini);
		exit(2);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("mini: exit: too many arguments", 2);
		return (1);
	}
	ft_putendl_fd("exit", 1);
	if (cmd->args[1])
		status = ft_atol(cmd->args[1]);
	free_values(mini);
	exit(status % 256);
}
