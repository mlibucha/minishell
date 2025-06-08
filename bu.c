/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:08 by e                 #+#    #+#             */
/*   Updated: 2025/06/06 10:29:08 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	mini_unset(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		del_env(&mini->env_list, cmd->args[i]);
	return (0);
}

int	mini_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;

	if (cmd->argc > 2)
	{
		ft_putendl_fd("mini: cd: too many arguments", 2);
		return (1);
	}
	if (cmd->argc == 1)
	{
		path = get_value(&mini->env_list, "HOME");
		if (path == NULL)
		{
			ft_putendl_fd("mini: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = cmd->args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("mini: cd: ", 2);
		perror(path);
		return (1);
	}
	return (update_path(mini), 0);
}

int	mini_pwd()
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("mini: pwd: ", 2);
		perror("");
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

int	mini_echo(t_cmd *cmd)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!ft_strcmp(cmd->args[1], "-n"))
	{
		option = 1;
		i++;
	}
	while (++i < cmd->argc - 1)
		printf("%s ", cmd->args[i]);
	printf("%s",cmd->args[i]);
	if (!option)
		printf("\n");
	return (0);
}

int	execute_builtin(t_mini *mini)
{
	int	a;

	a = mini->cmd_count - 1;
	if (ft_strcmp(mini->cmds[a]->cmd, "exit") == 0)
		return (mini_exit(mini->cmds[a], mini, a));
	else if (ft_strcmp(mini->cmds[a]->cmd, "cd") == 0)
		return (mini_cd(mini->cmds[a], mini));
	else if (ft_strcmp(mini->cmds[a]->cmd, "pwd") == 0)
		return (mini_pwd());
	else if (ft_strcmp(mini->cmds[a]->cmd, "echo") == 0)
		return (mini_echo(mini->cmds[a]));
	else if (ft_strcmp(mini->cmds[a]->cmd, "unset") == 0)
		return (mini_unset(mini, mini->cmds[a]));
	else if (ft_strcmp(mini->cmds[a]->cmd, "export") == 0)
		return (mini_export(mini->cmds[a], mini));
	else if (ft_strcmp(mini->cmds[a]->cmd, "env") == 0)
		return (mini_env(mini->cmds[a], mini));
	return (-1);
}
