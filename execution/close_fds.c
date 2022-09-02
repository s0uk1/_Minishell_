/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:58:48 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/02 11:02:59 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//if you close default in and out fds the parent exits ??
int	close_all(t_cmd *lst_cmd, int **pipes, int count);
{
	int	idx;
	t_cmd	*cmd;
	
	idx = 0;
	cmd = lst_cmd;
	while (cmd)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	while (idx < count - 1)
	{
		close(pipes[idx][1]);
		close(pipes[idx][0]);
		idx++;
	}
	idx = 0;
	while (idx < count - 1)
		free(pipes[idx++]);
	free(pipes);
	return (0);
}
