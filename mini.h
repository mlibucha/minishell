/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:03:37 by e                 #+#    #+#             */
/*   Updated: 2025/06/18 13:46:57 by e                ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include "get_next_line_bonus.h"
# define TEMP_SPACE_REPLACEMENT '\x1F'

typedef struct s_heredoc1
{
	char				*content;
	struct s_heredoc1	*next;
}	t_heredoc;

typedef struct s_cmd
{
	char		*cmd;
	char		**args;
	int			argc;
	bool		input_redir;
	char		*input_file;
	bool		output_redir;
	char		**output_files;
	int			output_count;
	bool		append;
	bool		heredoc;
	char		**heredoc_delim;
	int			pipe_out;
	bool		pipe_in;
	t_heredoc	*heredoc_list;
	int			heredoc_count;
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
	t_cmd	**cmds;
	int		cmd_count;
	int		status;
	int		last_status;
	char	*full_path;
	t_env	*env_list;
	char	**envp;
	int		cmd_left;
}	t_mini;

void	set_values(t_mini *mini);
void	free_values(t_mini *mini);
int		read_input(t_mini *mini);
int		execute_command(t_mini *mini);
void	update_path(t_mini *mini);
void	update_env_array(t_mini *mini);
char	**convert_env_list_to_array(t_env *env_list);

void	list_del(t_env **lst, char *key);
void	list_add(t_env **lst, char *key, char *value);
void	swap_value(t_env **lst, char *key, char *value);
void	destroy_list(t_env **lst);
char	*get_value(t_env **lst, char *key);
int		execute_builtin(t_mini *mini, int a);
t_env	*init_envs(char **envp, t_mini *mini);
void	print_envs(t_env **list);
void	del_env(t_env **list, char *key);
void	add_env(t_env **list, char *key, char *value, t_mini mini);
char	*split_value(char *str);
char	*split_key(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	free_cmd(t_cmd *cmds);
void	parse_to_cmd(t_mini *mini, char **args);
void	init_cmd(t_cmd *cmd);
void	free_all_cmds(t_mini *mini);
int		execute_pipeline(t_mini *mini);
char	*find_command_path(char *cmd, t_env *env_list);
int		setup_redirections(t_cmd *cmd);
int		handle_heredoc(t_cmd *cmd);
int		mini_exit(t_cmd *cmd, t_mini *mini, int a);
int		mini_export(t_cmd *cmd, t_mini *mini);
int		mini_env(t_cmd *cmd, t_mini *mini);
void	handler(int signal, siginfo_t *info, void *context);
void	exec_single_cmd(t_mini *mini, t_cmd *cmd);
char	*transform_quotes(char *str, t_mini mini);
void	transform_spaces(char **args);
char	*replace(char *s, char *var, char *val, int pos);
void	find_env(char **str, t_env *env_list, int pos);
int		execute_builtin2(t_cmd *cmd, t_mini *mini, int a);
void	free_env_array(char **env_array);
void	free_heredoc_list(t_heredoc *list);
void	check_question_mark(char **str, int d, t_mini mini);
void	swap_characters(char *str, int *d, char c);
int		ft_find_sec_quote(char *str, int i, char c);
int		ft_find_len_quote(char *str, int i);
int		export_one_arg(t_mini *mini);
int		calc_cmd_count(char **args);
void	heredoc(t_cmd *cmd, char **args, int *i, int end);
char	*extend_envs(char *input, t_mini *mini);
char	*handle_normal_replacement(char *s, char *val, int pos, int var_len, int s_len, int val_len);
void	input_redir(t_cmd *cmd, char **args, int *i, int end);
void	output_redir(t_cmd *cmd, char **args, int *i, int end);
#endif