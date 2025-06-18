/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:00:00 by e                 #+#    #+#             */
/*   Updated: 2025/06/18 12:10:13 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		free_all_cmds(mini);
		exit(127);
	}
	execve(cmd_path, cmd->args, mini->envp);
	free_all_cmds(mini);
	perror("mini: execve");
	free(cmd_path);
}

int	execute_command(t_mini *mini)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (mini->cmd_count == 1)
	{
		if (handle_heredoc(mini->cmds[0]))
			return (0);
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
