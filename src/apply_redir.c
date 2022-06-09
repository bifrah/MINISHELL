/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:13:55 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/04 16:13:58 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	del_red(void *ptr)
{
	t_red	*red;

	red = (t_red *)ptr;
	if (red->word)
		free(red->word);
	free(red);
}

int	apply_single_redir(t_red *red)
{
	int	flags;
	int	fd;

	if (!red || ! red->word)
		return (-1);
	flags = (red->in_out == RED_IN) * O_RDONLY
		| (red->in_out == RED_OUT) * (O_CREAT | O_WRONLY);
	if (red->in_out == RED_OUT)
		flags |= (red->mode == RED_TRUNC) * O_TRUNC
			| (red->mode == RED_APPEND) * O_APPEND;
	fd = open(red->word, flags, 0644);
	if (fd < 0)
		return (ft_err4("minishell", red->word, strerror(errno), NULL) - 1);
	if (red->in_out == RED_IN && red->mode == RED_APPEND)
		unlink(red->word);
	if (dup2(fd, red->fd) < 0)
		return (-1);
	close(fd);
	return (0);
}

int	apply_redir(t_cmd *cmd)
{
	t_list	*head;
	int		ret;

	ret = 0;
	head = cmd->red;
	while (head && !ret)
	{
		ret = apply_single_redir(head->data);
		head = head->next;
	}
	return (ret);
}

int	exec_script(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_err4("minishell", path, strerror(errno), NULL);
		return (-1);
	}
	if (dup2(fd, 0) < 0)
		return (-1);
	close(fd);
	return (0);
}
