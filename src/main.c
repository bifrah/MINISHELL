/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:17:47 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 17:42:22 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_xt_stat = 0;

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;
	int		ret_main1;

	sig_init(SIGINT, SIG_IGN);
	sig_init(SIGQUIT, SIG_IGN);
	if (!envp)
		exit (EXIT_FAILURE);
	if (new_sh(ac, av, envp, &sh) < 0)
		return (-1);
	if (isatty(0))
		printf("Welcome to minishell \"Final Push Edition\"!\n");
	while (1)
	{
		ret_main1 = main_part1(&sh);
		if (ret_main1 > ERR_SYNTAX && ret_main1 < 0)
			break ;
		if (ret_main1 != ERR_SYNTAX && ret_main1 != ERR_DOC && main_part2(&sh))
			break ;
		del_split(sh.pipeline, &del_cmd);
		sh.pipeline = NULL;
	}
	del_sh(&sh);
	clear_history();
	return (g_xt_stat);
}
