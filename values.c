/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:01:16 by e                 #+#    #+#             */
/*   Updated: 2025/06/18 17:20:29 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	update_path(t_mini *mini)
{
	char	*pwd;

	if (!mini)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("mini: error: cannot get current directory: ", 2);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		mini->status = 1;
		return ;
	}
	if (mini->path)
		free(mini->path);
	mini->path = ft_strdup(pwd);
	if (!mini->path)
	{
		free(pwd);
		mini->status = 1;
		return ;
	}
	add_env(&mini->env_list, "PWD", pwd);
	free(pwd);
	mini->status = 0;
}

void	set_values(t_mini *mini)
{
	mini->envp = NULL;
	mini->path = NULL;
	mini->cmds = NULL;
	mini->cmd_count = 0;
	mini->status = 0;
	mini->last_status = 0;
}

void	free_values(t_mini *mini)
{
	if (mini->path)
	{
		free(mini->path);
		mini->path = NULL;
	}
	if (mini->cmds)
	{
		free_all_cmds(mini);
		mini->cmds = NULL;
	}
	if (mini->envp)
	{
		free_env_array(mini->envp);
		mini->envp = NULL;
	}
	if (mini->env_list)
	{
		destroy_list(&mini->env_list);
		mini->env_list = NULL;
	}
	free(mini);
}
