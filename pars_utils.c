/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:04:44 by emil              #+#    #+#             */
/*   Updated: 2025/06/18 16:04:57 by e                ###   ########.fr       */
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

int	calc_cmd_count(char **args)
{
	int	cmd_count;
	int	i;

	cmd_count = 1;
	i = -1;
	while (args[++i])
		if (!ft_strcmp(args[i], "|"))
			cmd_count++;
	return (cmd_count);
}

void	heredoc(t_cmd *cmd, char **args, int *i, int end)
{
	char	**new_delims;

	if(cmd->heredoc_delim)
		ft_free(cmd->heredoc_delim);
	cmd->heredoc = true;
	(*i)++;
	if (*i < end)
	{
		new_delims = malloc((cmd->heredoc_count + 1) * sizeof(char *));
		if (!new_delims)
			return ;
		cmd->heredoc_delim = new_delims;
		cmd->heredoc_delim[cmd->heredoc_count] = ft_strdup(args[*i]);
		cmd->heredoc_count++;
	}
}
