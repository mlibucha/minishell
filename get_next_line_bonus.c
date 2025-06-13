/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:11:35 by mlibucha          #+#    #+#             */
/*   Updated: 2025/06/13 14:11:10 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_nodes(e_list **list)
{
	e_list	*last_node;
	e_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(e_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	ft_free_nodes(list, clean_node, buf);
}

char	*get_line(e_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	ft_append_nodes(e_list **list, char *buf, int fd)
{
	e_list	*new_node;
	e_list	*last_node;

	new_node = malloc(sizeof(e_list));
	if (new_node == NULL)
		return ;
	new_node->str_buf = buf;
	new_node->next = NULL;
	if (list[fd] == NULL)
		list[fd] = new_node;
	else
	{
		last_node = find_last_node(list[fd]);
		if (last_node != NULL)
			last_node->next = new_node;
	}
}

void	create_list(e_list **list, int fd)
{
	int		char_read;
	char	*buf;

	if (list[fd] == NULL)
		list[fd] = NULL;
	while (!found_newline(list[fd]))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		ft_append_nodes(list, buf, fd);
	}
}

char	*get_next_line(int fd)
{
	static e_list	*list[1024];
	char			*next_line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(list, fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = get_line(list[fd]);
	clear_nodes(&list[fd]);
	return (next_line);
}
