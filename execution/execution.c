/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by rsaf              #+#    #+#             */
/*   Updated: 2022/08/31 16:46:52 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute_cmd(t_data *data, char *path, t_cmd *lst_cmd)
{
	if (lst_cmd->fd_in != 0)
		close(lst_cmd->fd_in);
	if (lst_cmd->fd_out != 1)
		close(lst_cmd->fd_out);
	execve(path, lst_cmd->cmd, data->env);
	perror("mshell: ");
	if (errno == EACCES)
		exit(126);
	exit (127);
}

int	cmds_lent(t_data *data)
{
	int		lent;
	t_cmd	*cmd_clone;

	lent = 0;
	cmd_clone = data->lst_cmd;
	while (cmd_clone)
	{
		lent++;
		cmd_clone = cmd_clone->next;
	}
	return (lent);
}

int	execution(t_data *data)
{
	int	**pip;
	int	pid;
	t_cmd *cmd;

	pid = 0;
	// data->general.pid = -42;
	// data->general.lent = cmds_lent(data);
	if (data->lst_cmd)
	{
		// ft_builtins(data, data->lst_cmd);
		pip = initialize_pipes(data);
		ft_print_cmd(data->lst_cmd);
	}
	// ft_get_paths(data);
	// if (data->lst_cmd)
	// 	start_execution(data, pip, 0);
	return (0);
}
