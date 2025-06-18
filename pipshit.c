/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipshit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:52:47 by e                 #+#    #+#             */
/*   Updated: 2025/06/18 12:21:54 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	create_pipe_if_needed(t_mini *mini, int i, int pipe_fd[2])
{
	if (i < mini->cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("mini: pipe");
			return (1);
		}
	}
	return (0);
}

static void	handel_child_p(t_mini *mini, int i, int prev_pipe, int pipe_fd[2])
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (i < mini->cmd_count - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	setup_redirections(mini->cmds[i]);
	if (handle_heredoc(mini->cmds[i]))
		exit(0);
	if (execute_builtin(mini, i) == 0)
		exit(0);
	exec_single_cmd(mini, mini->cmds[i]);
}

static void	cleanup_pipes(int *prev_pipe, int pipe_fd[2], t_mini *mini, int i)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (i < mini->cmd_count - 1)
	{
		close(pipe_fd[1]);
		*prev_pipe = pipe_fd[0];
	}
}

int	execute_pipeline(t_mini *mini)
{
	int		pipe_fd[2];
	int		prev_pipe;
	int		status;
	pid_t	pid;
	int		i;

	prev_pipe = -1;
	i = -1;
	while (++i < mini->cmd_count)
	{
		if (create_pipe_if_needed(mini, i, pipe_fd))
			return (1);
		pid = fork();
		if (pid == 0)
			handel_child_p(mini, i, prev_pipe, pipe_fd);
		else if (pid < 0)
		{
			perror("mini: fork");
			return (1);
		}
		cleanup_pipes(&prev_pipe, pipe_fd, mini, i);
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		mini->status = WEXITSTATUS(status);
	return (mini->status);
}
