#include "mini.h"

// void whiele_loop(t_mini *cmd, int *i, char **args, int end)
// {
// 	if (!ft_strcmp(args[i], ">"))
// 		{
// 			cmd->output_redir = 1;
// 			i++;
// 			if (i < end)
// 				cmd->output_file = ft_strdup(args[i]);
// 		}
// 		else if (!ft_strcmp(args[i], ">>"))
// 		{
// 			cmd->output_redir = 1;
// 			cmd->append = 1;
// 			i++;
// 			if (i < end)
// 				cmd->output_file = ft_strdup(args[i]);
// 		}
// 		else if (!ft_strcmp(args[i], "<<"))
// 		{
// 			cmd->heredoc = 1;
// 			i++;
// 			if (i < end)
// 				cmd->heredoc_delim = ft_strdup(args[i]);
// 		}
// 		else
// 		{
// 			if (j == 0)
// 				cmd->cmd = ft_strdup(args[i]);
// 			cmd->args[j++] = ft_strdup(args[i]);
// 		}
// }

t_cmd *create_cmd(char **args, int start, int end)
{
	t_cmd   *cmd;
	int     i;
	int     j;
	
	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	cmd->args = malloc((end - start + 1) * sizeof(char *));
	j = 0;
	i = start;
	while (i < end)
	{
		if (!ft_strcmp(args[i], "|"))
			cmd->pipe_out = 1;
		else if (!ft_strcmp(args[i], "<"))
		{
			cmd->input_redir = 1;
			i++;
			if (i < end)
				cmd->input_file = ft_strdup(args[i]);
		}
		else if (!ft_strcmp(args[i], ">"))
		{
			cmd->output_redir = 1;
			i++;
			if (i < end)
				cmd->output_file = ft_strdup(args[i]);
		}
		else if (!ft_strcmp(args[i], ">>"))
		{
			cmd->output_redir = 1;
			cmd->append = 1;
			i++;
			if (i < end)
				cmd->output_file = ft_strdup(args[i]);
		}
		else if (!ft_strcmp(args[i], "<<"))
		{
			cmd->heredoc = 1;
			i++;
			if (i < end)
				cmd->heredoc_delim = ft_strdup(args[i]);
		}
		else
		{
			if (j == 0)
				cmd->cmd = ft_strdup(args[i]);
			cmd->args[j++] = ft_strdup(args[i]);
		}
		// whiele_loop(cmd, &i, args, end);
		i++;
	}
	cmd->args[j] = NULL;
	cmd->argc = j;
	return (cmd);
}

void parse_to_cmd(t_mini *mini, char **args)
{
	int     i;
	int     start;
	int     cmd_count;
	t_cmd   **cmds;
	
	cmd_count = 1;
	i = -1;
	while (args[++i])
		if (!ft_strcmp(args[i], "|"))
			cmd_count++;
	cmds = malloc(cmd_count * sizeof(t_cmd *));
	if (!cmds)
		return; // Handle allocation failure
	start = 0;
	i = -1;
	mini->cmd_count = 0; // Initialize cmd_count here
	while (args[++i])
	{
		if (!ft_strcmp(args[i], "|"))
		{
			cmds[mini->cmd_count++] = create_cmd(args, start, i);
			start = i + 1;
		}
	}
	cmds[mini->cmd_count++] = create_cmd(args, start, i);
	i = 0;
	while (++i < mini->cmd_count)
		cmds[i]->pipe_in = 1;
	mini->cmds = cmds;
	free(args);
}
