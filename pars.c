/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:40:06 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/10 20:25:33 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	input_redir(t_cmd *cmd, char **args, int *i, int end)
{
	cmd->input_redir = true;
	(*i)++;
	if (*i < end)
		cmd->input_file = ft_strdup(args[*i]);
}

void	output_redir(t_cmd *cmd, char **args, int *i, int end)
{
	cmd->output_redir = true;
	if (!ft_strcmp(args[*i], ">>"))
		cmd->append = true;
	(*i)++;
	if (*i < end)
	{
		cmd->output_files[cmd->output_count] = ft_strdup(args[*i]);
		cmd->output_count++;
	}
}

void	heredoc(t_cmd *cmd, char **args, int *i, int end)
{
	cmd->heredoc = true;
	(*i)++;
	if (*i < end)
		cmd->heredoc_delim = ft_strdup(args[*i]);
}

t_cmd	*create_cmd(char **args, int start, int end)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	cmd->args = malloc((end - start + 1) * sizeof(char *));
	cmd->output_files = malloc((end - start + 1) * sizeof(char *));
	j = 0;
	i = start;
	while (i < end)
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
	return (cmd);
}

void	parse_to_cmd(t_mini *mini, char **args)
{
	int		i;
	int		start;
	int		cmd_count;
	t_cmd	**cmds;

	cmd_count = 1;
	i = -1;
	while (args[++i])
		if (!ft_strcmp(args[i], "|"))
			cmd_count++;
	cmds = malloc(cmd_count * sizeof(t_cmd *));
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
		cmds[i]->pipe_in = true;
	mini->cmds = cmds;
	free(args);
}
