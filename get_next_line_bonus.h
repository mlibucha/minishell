/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: e <e@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:29:08 by mlibucha          #+#    #+#             */
/*   Updated: 2025/06/18 17:07:46 by e                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct t_elist
{
	char			*str_buf;
	struct t_elist	*next;
}				t_elist;

char	*get_next_line(int fd);
void	ft_creatlist(t_elist **list, int fd);
void	ft_append_nodes(t_elist **list, char *buf, int fd);
char	*get_line(t_elist *list);
int		len_to_newline(t_elist *list);
void	copy_str(t_elist *list, char *str);
void	clear_nodes(t_elist **list);
int		found_newline(t_elist *list);
t_elist	*find_last_node(t_elist *list);
void	ft_free_nodes(t_elist **list, t_elist *clean_node, char *buf);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif
