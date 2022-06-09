/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:58 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 13:36:04 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sa_main_handler(int x)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_xt_stat = x + 128;
}

void	sa_heredoc_handler(int x)
{
	write(1, "\n", 1);
	close(0);
	close(1);
	close(2);
	exit(128 + x);
}

int	sig_init(int signo, void (*handler_fct)(int))
{
	struct sigaction	act;

	act.sa_handler = handler_fct;
	act.sa_flags = 0;
	sigemptyset(&(act.sa_mask));
	sigaction(signo, &act, NULL);
	return (0);
}
