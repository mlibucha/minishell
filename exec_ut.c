#include "mini.h"

char *ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t 	len1;
	size_t 	len2;
	size_t 	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	str = malloc(len1 + len2 + len3 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	ft_memcpy(str + len1 + len2, s3, len3);
	str[len1 + len2 + len3] = '\0';
	return (str);
}

char **convert_env_list_to_array(t_env *env_list)
{
	t_env	*current;
	char	**env_array;
	int		count;
	int		i;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->key && current->value)
			count++;
		current = current->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->key && current->value)
		{
			env_array[i] = ft_strjoin3(current->key, "=", current->value);
			if (!env_array[i])
			{
				while (--i >= 0)
					free(env_array[i]);
				free(env_array);
				return (NULL);
			}
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char *find_command_path(char *cmd, t_env *env_list)
{
	char	*path;
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_value(&env_list, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, X_OK) == 0)
		{
			ft_free(paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_free(paths);
	return (NULL);
}
