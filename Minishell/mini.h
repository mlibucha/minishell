/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:03:37 by e                 #+#    #+#             */
/*   Updated: 2025/05/14 19:23:21 by estolarc         ###   ########.fr       */
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
	char	**args;
	t_env	envs;
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
}	t_mini;


void	set_values(t_mini *mini, char **envp);
void	free_values(t_mini *mini);
int		read_input(t_mini *mini);
int		parse_input(t_mini *mini, char *input);
int		execute_commands(t_mini *mini);
int		execute_command(char **args, t_mini *mini);
int		execute_builtin(t_mini *mini, t_cmd *cmd);
int		handle_redirections(t_cmd *cmd);
void	reset_redirections(t_cmd *cmd);
void	update_path(t_mini *mini);
char	*find_executable(char *cmd);

int		mini_exit(t_mini *mini, t_cmd *cmd);
int		mini_cd(t_mini *mini, t_cmd *cmd);
int		mini_pwd(t_mini *mini, t_cmd *cmd);
int		mini_echo(t_mini *mini, t_cmd *cmd);
int		mini_env(t_mini *mini, t_cmd *cmd);
int		mini_export(t_mini *mini, t_cmd *cmd);
int		mini_unset(t_mini *mini, t_cmd *cmd);

char	*ft_strtok(char *str, const char *delim);

void	list_del(t_env **lst, char *key);
void	list_add(t_env **lst, char *key, char *value);
void	swap_value(t_env **lst, char *key, char *value);
void	destroy_list(t_env **lst);
char	*get_value(t_env **lst, char *key);

t_env	*init_envs(char **envp, t_mini *mini);
void	print_envs(t_env **list);
#endif