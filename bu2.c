/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:00 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/15 15:19:44 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**ft_arraydup(char **array)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (array[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	ft_sort_array(char **array)
{
	int		i;
	int		j;
	char	*temp;
	int		len;

	len = 0;
	while (array[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	mini_export(t_cmd *cmd, t_mini *mini)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (cmd->argc == 1)
	{
		update_env_array(mini);
		char **env_copy = ft_arraydup(mini->envp);
		if (!env_copy)
			return (1);
		ft_sort_array(env_copy);
		i = 0;
		while (env_copy[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(env_copy[i], STDOUT_FILENO);
			i++;
		}
		ft_free(env_copy);
		return (0);
	}
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
