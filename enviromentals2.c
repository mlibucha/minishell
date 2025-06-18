/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromentals2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 05:17:59 by emil              #+#    #+#             */
/*   Updated: 2025/06/18 17:20:18 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_key_and_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

t_env	*init_envs(char **envp, t_mini *mini)
{
	t_env	*list;
	int		i;
	char	*key;
	char	*value;

	i = -1;
	list = NULL;
	while (envp[++i])
	{
		key = split_key(envp[i]);
		value = split_value(envp[i]);
		if (key && value)
		{
			add_env(&list, key, value);
			free(key);
			free(value);
		}
		else
			free_key_and_value(key, value);
	}
	if (mini->envp)
		free_env_array(mini->envp);
	return (list);
}

void	print_envs(t_env **list)
{
	t_env	*node;

	node = *list;
	while (node)
	{
		printf("%s=", node->key);
		if (node->value)
			printf("%s", node->value);
		printf("\n");
		node = node->next;
	}
}
