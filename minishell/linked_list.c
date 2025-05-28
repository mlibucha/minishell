/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:28:01 by estolarc          #+#    #+#             */
/*   Updated: 2025/05/25 19:04:36 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;

	a = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[a] != '\0' || s2[a] != '\0')
	{
		if (s1[a] != s2[a])
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		a++;
	}
	return (0);
}

char	*get_value(t_env **lst, char *key)
{
	t_env	*node;

	if (!lst || !key)
		return (NULL);
	node = *lst;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	destroy_list(t_env **lst)
{
	t_env *tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	swap_value(t_env **lst, char *key, char *value)
{
	t_env	*node;

	node = *lst;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			node->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
}

void	list_add(t_env **lst, char *key, char *value)
{
	t_env	*node;
	t_env	*new;

	new = malloc (sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
}

void	list_del(t_env **lst, char *key)
{
	t_env	*node;
	t_env	*tmp;

	node = *lst;
	if (!ft_strcmp((*lst)->key, key))
	{
		*lst = (*lst)->next;
		free(node->key);
		free(node->value);
		free(node);
		return ;
	}
	while (node->next != NULL)
	{
		if (!ft_strcmp(node->next->key, key))
		{
			tmp = node->next;
			node->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		node = node->next;
	}
}
