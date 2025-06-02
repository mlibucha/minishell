/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:08 by e                 #+#    #+#             */
/*   Updated: 2025/05/29 19:47:03 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_isnumber(char *str)
{
	int	a;

	a = -1;
	while (str[++a])
	{
		if (str[a] < '0' || str[a] > '9')
			return (0);
	}
	return (1);
}

int	mini_unset(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		del_env(&mini->env_list, cmd->args[i]);
	return (0);
}

int	mini_exit(t_cmd *cmd, t_mini *mini, int a)
{
	long int	status;

	status = 0;
	if (a != 0)
		return (1);
	if (!ft_isnumber(cmd->args[1]))
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
		status = ft_atoi("123");
	free_values(mini);
	exit(status);
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
	update_path(mini);
	return (0);
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

int	mini_echo(t_mini *mini)
{
	int	i;
	int	newline;

	(void)mini;
	newline = 1;
	i = 1;
	if (mini->cmds[0]->argc > 1
		&& ft_strncmp(mini->cmds[0]->args[1], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (i < mini->cmds[0]->argc)
	{
		ft_putstr_fd(mini->cmds[0]->args[i], 1);
		if (i < mini->cmds[0]->argc - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
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
		return (mini_echo(mini));
	else if (ft_strcmp(mini->cmds[a]->cmd, "unset") == 0)
		return (mini_unset(mini, mini->cmds[a]));
	else if (ft_strcmp(mini->cmds[a]->cmd, "export") == 0)
		return (mini_echo(mini));
	else if (ft_strcmp(mini->cmds[a]->cmd, "env") == 0)
		return (print_envs(&mini->env_list), 1);
	return (-1);
}
