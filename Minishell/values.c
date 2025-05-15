/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:01:16 by e                 #+#    #+#             */
/*   Updated: 2025/05/14 15:01:33 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void set_values(t_mini *mini, char **envp)
{
	mini->path = NULL;
	mini->cmds = NULL;
	mini->cmd_count = 0;
	mini->pipe_count = 0;
	mini->status = 0;
	mini->last_status = 0;
}

void free_values(t_mini *mini)
{
	int i;

	if (mini->path)
		free(mini->path);
	if (mini->cmds)
	{
		i = 0;
		while (i < mini->cmd_count)
		{
			free(mini->cmds[i].args);
			if (mini->cmds[i].input)
				free(mini->cmds[i].input);
			if (mini->cmds[i].output)
				free(mini->cmds[i].output);
			i++;
		}
		free(mini->cmds);
	}
}