/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:40:06 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/18 18:47:49 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*init_cmd_struct(int arg_count)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	cmd->args = malloc((arg_count + 1) * sizeof(char *));
	cmd->output_files = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd->args || !cmd->output_files)
	{
		free(cmd->args);
		free(cmd->output_files);
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < arg_count + 1)
	{
		cmd->output_files[i] = NULL;
		i++;
	}
	cmd->argc = 0;
	cmd->output_count = 0;
	return (cmd);
}

void	populate_cmd(t_cmd *cmd, char **args, int start, int end)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (i < end && args[i])
	{
		if (!ft_strcmp(args[i], "|"))
			cmd->pipe_out = 1;
		else if (!ft_strcmp(args[i], "<"))
			input_redir(cmd, args, &i, end);
		else if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>"))
			output_redir(cmd, args, &i, end);
		else if (!ft_strcmp(args[i], "<<"))
			heredoc(cmd, args, &i, end);
		else
		{
			if (j == 0)
				cmd->cmd = ft_strdup(args[i]);
			cmd->args[j++] = ft_strdup(args[i]);
		}
		i++;
	}
	cmd->args[j] = NULL;
	cmd->argc = j;
}

t_cmd	*create_cmd(char **args, int start, int end)
{
	t_cmd	*cmd;

	if (!args || end <= start)
		return (NULL);
	cmd = init_cmd_struct(end - start);
	if (!cmd)
		return (NULL);
	populate_cmd(cmd, args, start, end);
	return (cmd);
}

void	parse_to_cmd(t_mini *mini, char **args)
{
	int		i;
	int		start;
	t_cmd	**cmds;

	cmds = malloc(calc_cmd_count(args) * sizeof(t_cmd *));
	if (!cmds)
		return ;
	start = 0;
	i = -1;
	mini->cmd_count = 0;
	while (args[++i])
	{
		if (!ft_strcmp(args[i], "|"))
		{
			cmds[mini->cmd_count++] = create_cmd(args, start, i);
			start = i + 1;
		}
	}
	cmds[mini->cmd_count++] = create_cmd(args, start, i);
	i = 0;
	while (++i < mini->cmd_count)
		if (cmds[i])
			cmds[i]->pipe_in = true;
	mini->cmds = cmds;
	ft_free(args);
}
