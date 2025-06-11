/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:00:00 by e                 #+#    #+#             */
/*   Updated: 2025/06/11 14:06:39 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	exec_single_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd_path;

	update_env_array(mini);
	cmd_path = find_command_path(cmd->cmd, mini->env_list);
	if (!cmd_path)
	{
		ft_putstr_fd("mini: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, cmd->args, mini->envp);
	perror("mini: execve");
	free(cmd_path);
	exit(EXIT_FAILURE);
}


int	execute_command(t_mini *mini)
{
	pid_t	pid;
	int		status;

	if (mini->cmd_count == 1)
	{
		if (mini->cmds[0]->heredoc)
			handle_heredoc(mini->cmds[0]);
		pid = fork();
		if (pid == 0)
		{
			write(1, "1\n", 2);
			setup_redirections(mini->cmds[0]);
			exec_single_cmd(mini, mini->cmds[0]);
		}
		else if (pid < 0)
			perror("mini: fork");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->status = WEXITSTATUS(status);
		return (mini->status);
	}
	return (execute_pipeline(mini));
}
