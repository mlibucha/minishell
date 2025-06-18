/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:04:44 by emil              #+#    #+#             */
/*   Updated: 2025/06/18 18:52:11 by e                ###   ########.fr       */
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

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	if (copy_size > 0)
		memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

void	heredoc(t_cmd *cmd, char **args, int *i, int end)
{
	char	**new_delims;

	cmd->heredoc = true;
	(*i)++;
	if (*i < end)
	{
		new_delims = ft_realloc(cmd->heredoc_delim,
				cmd->heredoc_count * sizeof(char *),
				(cmd->heredoc_count + 1) * sizeof(char *));
		if (!new_delims)
			return ;
		cmd->heredoc_delim = new_delims;
		cmd->heredoc_delim[cmd->heredoc_count] = ft_strdup(args[*i]);
		cmd->heredoc_count++;
	}
}
