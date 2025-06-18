/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emil <emil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:49:54 by e                 #+#    #+#             */
/*   Updated: 2025/06/16 05:36:28 by emil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_mini				*mini;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	(void)argv;
	if (argc != 1)
		return (1);
	if (envp == NULL)
	{
		fprintf(stderr, "Error: envp is NULL\n");
		return (1);
	}
	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		perror("malloc");
		return (1);
	}
	set_values(mini);
	mini->env_list = init_envs(envp, mini);
	read_input(mini);
	return (0);
}
