/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlibucha <mlibucha@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:03:37 by e                 #+#    #+#             */
/*   Updated: 2025/05/16 08:41:58 by mlibucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define MAX_ARGS 64
# define MAX_PIPES 10

typedef struct s_cmd
{
	char	*cmd;
	char	*args[MAX_ARGS];
	int		argc;
	int		counter;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	char	*path;
	t_cmd	*cmds;
	int		cmd_count;
	int		pipe_count;
	int		status;
	int		last_status;
	char	*full_path;
	t_env	*env_list;
	char	**envp;
}	t_mini;


void	set_values(t_mini *mini);
void	free_values(t_mini *mini);
int		read_input(t_mini *mini);
int		execute_command(t_mini *mini);
int		execute_builtin(t_mini *mini);
void	update_path(t_mini *mini);
void	update_env_array(t_mini *mini);
char	**convert_env_list_to_array(t_env *env_list);
void	add_env(t_env **list, char *key, char *value, t_mini mini);
void	list_del(t_env **lst, char *key);
void	list_add(t_env **lst, char *key, char *value);
void	swap_value(t_env **lst, char *key, char *value);
void	destroy_list(t_env **lst);
char	*get_value(t_env **lst, char *key);
int		execute_builtin(t_mini *mini);
t_env *init_envs(char **envp, t_mini mini);
void	print_envs(t_env **list);

void	del_env(t_env **list, char *key);

int	ft_strcmp(const char *s1, const char *s2);

#endif