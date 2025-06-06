/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:00 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/02 18:29:53 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	mini_export(t_cmd *cmd, t_mini *mini)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (++i < cmd->argc)
	{
		key = split_key(cmd->args[i]);
		value = split_value(cmd->args[i]);
		if (key)
		{
			add_env(&mini->env_list, key, value, *mini);
			free(key);
			free(value);
		}
	}
	return (0);
}

int	mini_env(t_cmd *cmd, t_mini *mini)
{
	if (cmd->argc > 1)
	{
		ft_putendl_fd("mini: env: too many arguments", 2);
		return (1);
	}
	print_envs(&mini->env_list);
	return (0);
}
