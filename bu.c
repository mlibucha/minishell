/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:08 by e                 #+#    #+#             */
/*   Updated: 2025/06/14 16:45:54 by e                ###   ########.fr       */
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

	if(mini->cmd_count != 1)
		return (0);
	if (cmd->argc > 2)
		return (ft_putendl_fd("mini: cd: too many arguments", 2), 1);
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

int	mini_pwd(void)
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
	printf("%s", cmd->args[i]);
	if (!option)
		printf("\n");
	return (0);
}

int	execute_builtin2(t_cmd *cmd, t_mini *mini, int a)
{
	int	ret;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	setup_redirections(cmd);
	ret = -1;
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		ret = mini_exit(cmd, mini, a);
	else if ((ft_strcmp(cmd->cmd, "cd") == 0 ))
		ret = mini_cd(cmd, mini);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ret = mini_pwd();
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ret = mini_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ret = mini_unset(mini, cmd);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ret = mini_export(cmd, mini);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ret = mini_env(cmd, mini);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	return (close(saved_stdin), close(saved_stdout), ret);
}
