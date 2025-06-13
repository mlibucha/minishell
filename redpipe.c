/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:09:20 by e                 #+#    #+#             */
/*   Updated: 2025/06/13 17:54:46 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int setup_input_redir(t_cmd *cmd)
{
	int fd;
	int saved_stdin = dup(STDIN_FILENO);

	if (!cmd->input_redir || !cmd->input_file)
		return 0;
		
	if (cmd->heredoc)
	{
		fd = open(cmd->input_file, O_RDONLY);
		unlink(cmd->input_file);
	}
	else
		fd = open(cmd->input_file, O_RDONLY);
		
	if (fd < 0)
	{
		perror("mini: input redirection");
		close(saved_stdin);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(saved_stdin);
	return 1;
}

int	setup_output_redir(t_cmd *cmd)
{
	int		fd;
	int		flags;
	int		i;
	char	*output_file;

	if (!cmd->output_redir || !cmd->output_files || cmd->output_count == 0)
		return 0;
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
	return 1;
}

int	setup_redirections(t_cmd *cmd)
{
	setup_input_redir(cmd);
	setup_output_redir(cmd);
	return 0;
}
