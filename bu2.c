/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emil <emil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:00 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/16 06:27:36 by emil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	mini_export(t_cmd *cmd, t_mini *mini)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (cmd->argc == 1)
		return (export_one_arg(mini));
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

int	execute_builtin(t_mini *mini, int a)
{
	int		ret;
	t_cmd	*cmd;

	cmd = mini->cmds[a];
	ret = -1;
	ret = execute_builtin2(cmd, mini, a);
	return (ret);
}
