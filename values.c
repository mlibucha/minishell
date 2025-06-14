/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:01:16 by e                 #+#    #+#             */
/*   Updated: 2025/06/14 16:49:03 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mini.h"

void    update_path(t_mini *mini)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_putstr_fd("mini: error: cannot get current directory: ", 2);
        ft_putendl_fd(strerror(errno), STDERR_FILENO);
        mini->status = 1;
        return;
    }
    if (mini->path)
        free(mini->path);
    mini->path = ft_strdup(pwd);
    add_env(&mini->env_list, "PWD", pwd, *mini);
    free(pwd);
    mini->status = 0;
}

void    set_values(t_mini *mini)
{
    mini->envp = NULL;
    mini->path = NULL;
    mini->cmds = NULL;
    mini->cmd_count = 0;
    mini->status = 0;
    mini->last_status = 0;
}

void    free_values(t_mini *mini)
{
    if (mini->path)
        free(mini->path);
    if (mini->cmds)
    {
        free(mini->cmds);
    }
}

void    free_cmd(t_cmd *cmd)
{
    int i;

    if (!cmd)
        return;
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
            free(cmd->args[i++]);
        free(cmd->args);
    }
    if (cmd->input_file)
        free(cmd->input_file);
    if (cmd->output_files)
    {
        i = 0;
        while (i < cmd->output_count)
            free(cmd->output_files[i++]);
        free(cmd->output_files);
    }
    if (cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    if (cmd->heredoc_list)
        free_heredoc_list(cmd->heredoc_list);
}

void    init_cmd(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->argc = 0;
    cmd->input_redir = false;
    cmd->input_file = NULL;
    cmd->output_redir = false;
    cmd->output_files = NULL;
    cmd->output_count = 0;
    cmd->append = false;
    cmd->heredoc = false;
    cmd->heredoc_delim = NULL;
    cmd->pipe_out = 0;
    cmd->pipe_in = false;
    cmd->heredoc_list = NULL;
}

void    free_all_cmds(t_mini *mini)
{
    int i;

    if (!mini || !mini->cmds)
        return;
    i = 0;
    while (i < mini->cmd_count)
    {
        if (mini->cmds[i])
        {
            free_cmd(mini->cmds[i]);
            free(mini->cmds[i]);
        }
        i++;
    }
    free(mini->cmds);
    mini->cmds = NULL;
    mini->cmd_count = 0;
}
