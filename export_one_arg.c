/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emil <emil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 06:15:43 by emil              #+#    #+#             */
/*   Updated: 2025/06/16 06:33:58 by emil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**ft_arraydup(char **array)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (array[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	ft_sort_array(char **array)
{
	int		i;
	int		j;
	char	*temp;
	int		len;

	len = 0;
	while (array[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	export_one_arg(t_mini *mini)
{
	int		i;
	char	**env_copy;

	update_env_array(mini);
	env_copy = ft_arraydup(mini->envp);
	if (!env_copy)
		return (1);
	ft_sort_array(env_copy);
	i = 0;
	while (env_copy[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(env_copy[i], STDOUT_FILENO);
		i++;
	}
	ft_free(env_copy);
	return (0);
}
