/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:49:54 by e                 #+#    #+#             */
/*   Updated: 2025/05/15 13:26:53 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	
	if(argc != 1)
		return (1);
	if (envp == NULL)
	{
		fprintf(stderr, "Error: envp is NULL\n");
		return (1);
	}
	t_mini *mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		perror("malloc");
		return (1);
	}
	set_values(mini);
	mini->env_list = init_envs(envp, *mini);
	read_input(mini);
	free_values(mini);
	free(mini);
	return (0);
}