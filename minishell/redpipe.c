/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:09:20 by e                 #+#    #+#             */
/*   Updated: 2025/05/28 11:35:05 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	setup_input_redir(t_cmd *cmd)
{
	int	fd;

	if (!cmd->input_redir || !cmd->input_file)
		return ;
	if (cmd->heredoc)
		fd = open(cmd->input_file, O_RDONLY);
	else
		fd = open(cmd->input_file, O_RDONLY);
	if (fd < 0)
	{
		perror("mini: input redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	setup_output_redir(t_cmd *cmd)
{
	int		fd;
	int		flags;
	int		i;
	char	*output_file;

	if (!cmd->output_redir || !cmd->output_files || cmd->output_count == 0)
		return ;
	i = -1;
	while (++i < cmd->output_count)
	{
		output_file = cmd->output_files[i];
		flags = O_WRONLY | O_CREAT;
		if (cmd->append)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		fd = open(output_file, flags, 0644);
		if (fd < 0)
		{
			perror("mini: output redirection");
			exit(EXIT_FAILURE);
		}
		if (i == cmd->output_count - 1)
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	setup_redirections(t_cmd *cmd)
{
	setup_input_redir(cmd);
	setup_output_redir(cmd);
}

void	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("mini: pipe");
		exit(EXIT_FAILURE);
	}
}

void	connect_pipes(int *prev_pipe, int pipe_fd[2], t_cmd *cmd)
{
	if (cmd->pipe_in && prev_pipe)
		dup2(*prev_pipe, STDIN_FILENO);
	if (cmd->pipe_out)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (prev_pipe)
		close(*prev_pipe);
	if (cmd->pipe_out)
		close(pipe_fd[1]);
}

void	wait_for_children(int *status)
{
	pid_t	wpid;

	wpid = wait(status);
	while (wpid > 0)
		wpid = wait(status);
}

int	execute_pipeline(t_mini *mini)
{
	int		pipe_fd[2];
	int		prev_pipe;
	int		status;
	int		i;
	pid_t	pid;

	prev_pipe = -1;
	i = -1;
	while (++i < mini->cmd_count)
	{
		if (i < mini->cmd_count - 1)
			create_pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			exec_child_process(mini, mini->cmds[i], prev_pipe,
							(i < mini->cmd_count - 1) ? pipe_fd[1] : STDOUT_FILENO);
		else if (pid < 0)
			perror("mini: fork");
		if (prev_pipe != -1)
			close(prev_pipe);
		if (i < mini->cmd_count - 1)
		{
			close(pipe_fd[1]);
			prev_pipe = pipe_fd[0];
		}
	}
	wait_for_children(&status);
	if (WIFEXITED(status))
		mini->status = WEXITSTATUS(status);
	return (mini->status);
}
