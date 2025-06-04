/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estolarc <estolarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:03:35 by estolarc          #+#    #+#             */
/*   Updated: 2025/06/03 19:41:08 by estolarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handler(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}
