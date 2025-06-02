/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:38:25 by e                 #+#    #+#             */
/*   Updated: 2025/05/28 by helper                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*generate_heredoc_filename(void)
{
	static int	counter = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(counter++);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", num);
	free(num);
	return (filename);
}

static void	read_heredoc_content(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("mini: warning: here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	int		fd;
	char	*filename;

	if (!cmd->heredoc || !cmd->heredoc_delim)
		return ;
	filename = generate_heredoc_filename();
	if (!filename)
	{
		perror("mini: heredoc");
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(filename);
		perror("mini: heredoc");
		exit(EXIT_FAILURE);
	}
	read_heredoc_content(fd, cmd->heredoc_delim);
	close(fd);
	cmd->input_redir = true;
	cmd->input_file = filename;
}
