
#include "mini.h"

void setup_input_redir(t_cmd *cmd)
{
	int fd;

	if (!cmd->input_redir || !cmd->input_file)
		return;
	fd = open(cmd->input_file, O_RDONLY);
	if (fd < 0)
	{
		perror("mini: input redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void setup_output_redir(t_cmd *cmd)
{
	int fd;
	int flags;

	if (!cmd->output_redir || !cmd->output_file)
		return;
	flags = O_WRONLY | O_CREAT;
	flags |= (cmd->append) ? O_APPEND : O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd < 0)
	{
		perror("mini: output redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void setup_redirections(t_cmd *cmd)
{
	setup_input_redir(cmd);
	setup_output_redir(cmd);
}

void create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("mini: pipe");
		exit(EXIT_FAILURE);
	}
}

void close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void connect_pipes(int *prev_pipe, int pipe_fd[2], t_cmd *cmd)
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

void wait_for_children(int *status)
{
	pid_t wpid;

	wpid = wait(status);
	while (wpid > 0)
		wpid = wait(status);
}

int execute_pipeline(t_mini *mini)
{
	int pipe_fd[2];
	int prev_pipe;
	int status;
	int i;

	prev_pipe = -1;
	i = 0;
	while (i < mini->cmd_count)
	{
		if (i < mini->cmd_count - 1)
			create_pipe(pipe_fd);
		pid_t pid = fork();
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
		i++;
	}
	wait_for_children(&status);
	if (WIFEXITED(status))
		mini->status = WEXITSTATUS(status);
	return (mini->status);
}
