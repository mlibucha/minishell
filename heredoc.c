/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:47:08 by e                 #+#    #+#             */
/*   Updated: 2025/06/13 17:52:50 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mini.h"

void display_heredoc_list(t_heredoc *list)
{
    t_heredoc *current;

    current = list;
    while (current)
    {
        if (current->content)
		{
            ft_putstr_fd(current->content, 1);
			ft_putstr_fd("\n", 1);
		}
        else
            ft_putstr_fd("(null content)\n", 1);
        current = current->next;
    }
}

static t_heredoc *create_heredoc_node(char *line)
{
	t_heredoc *node;

	node = malloc(sizeof(t_heredoc));
	if (!node)
		return (NULL);
	node->content = ft_strdup(line);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void add_to_heredoc_list(t_heredoc **list, t_heredoc *new)
{
	t_heredoc *current;

	if (!*list)
	{
		*list = new;
		return;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}

static void read_heredoc_content(t_heredoc **list, char *delimiter)
{
	char    *line;
	char    *trimmed_line;

	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		trimmed_line = line;
		while (*trimmed_line && *trimmed_line != '\n')
			trimmed_line++;
		*trimmed_line = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		add_to_heredoc_list(list, create_heredoc_node(line));
		free(line);
	}
	display_heredoc_list(*list);
}

void handle_heredoc(t_cmd *cmd)
{
	t_heredoc *heredoc_list;

	if (!cmd->heredoc || !cmd->heredoc_delim)
		return;
	heredoc_list = NULL;
	cmd->output_redir = true;
	read_heredoc_content(&heredoc_list, cmd->heredoc_delim);
	cmd->heredoc_list = heredoc_list;
	if (cmd->input_file)
	{
		free(cmd->input_file);
		cmd->input_file = NULL;
	}
}

void free_heredoc_list(t_heredoc *list)
{
	t_heredoc *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
	}
}