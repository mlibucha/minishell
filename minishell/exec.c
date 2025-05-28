/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:00:00 by e                 #+#    #+#             */
/*   Updated: 2025/05/28 11:35:22 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_single_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd_path;

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

void	exec_child_process(t_mini *mini, t_cmd *cmd, int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	setup_redirections(cmd);
	exec_single_cmd(mini, cmd);
}

int	execute_command(t_mini *mini)
{
	pid_t	pid;
	int		status;

	printf("%d\n", mini->cmd_count);
	if (mini->cmd_count == 1)
	{
		if (mini->cmds[0]->heredoc)
			handle_heredoc(mini->cmds[0]);
		pid = fork();
		if (pid == 0)
		{
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
