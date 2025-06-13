/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:29:08 by mlibucha          #+#    #+#             */
/*   Updated: 2025/06/13 14:11:12 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct e_list
{
	char			*str_buf;
	struct e_list	*next;
}				e_list;

char	*get_next_line(int fd);
void	ft_creatlist(e_list **list, int fd);
void	ft_append_nodes(e_list **list, char *buf, int fd);
char	*get_line(e_list *list);
int		len_to_newline(e_list *list);
void	copy_str(e_list *list, char *str);
void	clear_nodes(e_list **list);
int		found_newline(e_list *list);
e_list	*find_last_node(e_list *list);
void	ft_free_nodes(e_list **list, e_list *clean_node, char *buf);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif
