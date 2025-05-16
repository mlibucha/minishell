/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:01:16 by e                 #+#    #+#             */
/*   Updated: 2025/05/16 08:54:49 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void update_path(t_mini *mini)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("mini: error: cannot get current directory: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		mini->status = 1;
		return ;
	}
		if (mini->path)
		free(mini->path);
	mini->path = ft_strdup(pwd);
	add_env(&mini->env_list, "PWD", pwd, *mini);
	free(pwd);
	mini->status = 0;

}

void set_values(t_mini *mini)
{
	mini->envp = NULL;
	mini->path = NULL;
	mini->cmds = NULL;
	mini->cmd_count = 0;
	mini->pipe_count = 0;
	mini->status = 0;
	mini->last_status = 0;
}

void free_values(t_mini *mini)
{

	if (mini->path)
		free(mini->path);
	if (mini->cmds)
	{

		free(mini->cmds);
	}
}