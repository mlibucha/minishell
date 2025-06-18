/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:50:02 by emil              #+#    #+#             */
/*   Updated: 2025/06/18 15:56:56 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_output_files(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->output_count)
		free(cmd->output_files[i++]);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_files)
	{
		free_output_files(cmd);
		free(cmd->output_files);
	}
	if (cmd->heredoc_delim)
		ft_free(cmd->heredoc_delim);
	if (cmd->heredoc_list)
		free_heredoc_list(cmd->heredoc_list);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->input_redir = false;
	cmd->input_file = NULL;
	cmd->output_redir = false;
	cmd->output_files = NULL;
	cmd->output_count = 0;
	cmd->append = false;
	cmd->heredoc = false;
	cmd->heredoc_delim = NULL;
	cmd->pipe_out = 0;
	cmd->pipe_in = false;
	cmd->heredoc_list = NULL;
	cmd->heredoc_count = 0;
}

void	free_all_cmds(t_mini *mini)
{
	int	i;

	if (!mini || !mini->cmds)
		return ;
	i = 0;
	while (i < mini->cmd_count)
	{
		if (mini->cmds[i])
		{
			free_cmd(mini->cmds[i]);
			free(mini->cmds[i]);
		}
		i++;
	}
	free(mini->cmds);
	mini->cmds = NULL;
	mini->cmd_count = 0;
}
