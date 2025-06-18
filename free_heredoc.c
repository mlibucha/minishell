/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emil <emil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:35:39 by emil              #+#    #+#             */
/*   Updated: 2025/06/16 04:37:54 by emil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_heredoc_list(t_heredoc *list)
{
	t_heredoc	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
	}
}
