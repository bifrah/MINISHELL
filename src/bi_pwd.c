/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:15:58 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/04 16:16:05 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_pwd(void)
{
	char	*buff;
	int		size;

	size = GNL_BUFFER_SIZE;
	while (1)
	{
		buff = malloc(size);
		if (!buff)
			exit(EXIT_FAILURE);
		if (getcwd(buff, size))
			break ;
		free(buff);
		if (errno != ERANGE || size > 0x8000)
		{
			ft_err4("minishell: pwd", strerror(errno), NULL, NULL);
			return (NULL);
		}
		size *= 2;
	}
	return (buff);
}

int	bi_pwd(t_sh *sh, t_cmd *cmd)
{
	char	*s;

	(void)sh;
	(void)cmd;
	s = get_pwd();
	if (s)
	{
		printf("%s\n", s);
		free(s);
		g_xt_stat = 0;
	}
	else
		g_xt_stat = 1;
	return (CMD_NOWAIT);
}
