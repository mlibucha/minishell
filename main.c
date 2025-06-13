/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:49:54 by e                 #+#    #+#             */
/*   Updated: 2025/06/13 13:21:28 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
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
	return (0);
}
