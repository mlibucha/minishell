/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromentals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:56:16 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/15 21:26:09 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*split_key(char *str)
{
	int		i;
	int		j;
	char	*key;

	i = -1;
	key = NULL;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
				return (NULL);
			key = malloc(i + 1);
			j = -1;
			while (++j < i)
				key[j] = str[j];
			key[j] = '\0';
			return (key);
		}
	}
	return (key);
}

char	*split_value(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*value;

	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			j = i;
			k = 0;
			while (str[j])
				j++;
			if (j - i < 2)
				return (NULL);
			value = malloc(j - i + 1);
			while (str[++i])
				value[k++] = str[i];
			value[k] = '\0';
			return (value);
		}
	}
	return (NULL);
}

void add_env(t_env **list, char *key, char *value, t_mini mini)
{
	if (!key)
		return;
		
	if (get_value(list, key) == NULL)
		list_add(list, key, value);
	else
		swap_value(list, key, value);
	if (mini.envp)
	{
		update_env_array(&mini);
	}
}

void	del_env(t_env **list, char *key)
{
	if (list == NULL || key == NULL)
		return ;
	list_del(list, key);
}

void update_env_array(t_mini *mini)
{
	char **new_env;
	
	if (!mini || !mini->env_list)
		return ;
	new_env = convert_env_list_to_array(mini->env_list);
	if (!new_env)
		return;
	if (mini->envp)
	{
	    free_env_array(mini->envp);
		mini->envp = NULL;
	}
	mini->envp = new_env;
	//free_env_array(new_env);
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
			add_env(&list, key, value, *mini);
			free(key);
			free(value);
		}
		else
		{
			if(key)
				free(key);
			if(value)
				free(value);
		}
	}
	if (mini->envp)
        free_env_array(mini->envp);
	// mini->envp = convert_env_list_to_array(list);
	mini->env_list = list;
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
