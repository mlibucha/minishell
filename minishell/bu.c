/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:08 by e                 #+#    #+#             */
/*   Updated: 2025/05/26 20:16:36 by e                ###   ########.fr       */
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

int	mini_exit(t_mini *mini)
{
	int	status;

	status = 0;
	if (mini->cmds[0]->argc > 2)
	{
		ft_putendl_fd("mini: exit: too many arguments", 2);
		return (1);
	}
	if (mini->cmds[0]->argc == 2)
	{
		if (!ft_isnumber(mini->cmds[0]->args[1]))
		{
			ft_putstr_fd("mini: exit: ", 2);
			ft_putstr_fd(mini->cmds[0]->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			status = 2;
		}
		else
			status = ft_atoi(mini->cmds[0]->args[1]);
	}
	free_values(mini);
	exit(status);
}

int	mini_cd(t_mini *mini)
{
	char	*path;

	if (mini->cmd_count > 2)
	{
		ft_putendl_fd("mini: cd: too many arguments", 2);
		return (1);
	}
	if (mini->cmd_count == 1)
		path = get_value(&mini->env_list, "HOME");
	else
		path = mini->cmds[0]->args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("mini: cd: ", 2);
		perror(path);
		return (1);
	}
	update_path(mini);
	return (0);
}

int	mini_pwd(t_mini *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	(void)mini;
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
	if (ft_strncmp(mini->cmds[0]->cmd, "exit", 4) == 0)
		return (mini_exit(mini));
	else if (ft_strncmp(mini->cmds[0]->cmd, "cd", 2) == 0)
		return (mini_cd(mini));
	else if (ft_strncmp(mini->cmds[0]->cmd, "pwd", 3) == 0)
		return (mini_pwd(mini));
	else if (ft_strncmp(mini->cmds[0]->cmd, "echo", 4) == 0)
		return (mini_echo(mini));
	// else if (ft_strncmp(mini->cmds->args[0], "unset", 5) == 0 && (mini->cmds->argc == 2));
	// 	del_env(mini->env_list, mini->cmds->args[1]);
	// // else if (ft_strncmp(mini->cmds->args[0], "", 5) == 0 && (mini->cmds->argc == 2));
	// // 	del_env(mini->env_list, mini->cmds->args[1]);
	return (-1);
}
