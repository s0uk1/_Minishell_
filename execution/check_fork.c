/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:50:24 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/18 17:29:34 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(t_data *data, t_cmd *cmd_lst)
{
	char	**cmd;

	cmd = cmd_lst->cmd;
	if (!ft_strcmp(cmd[0], "export"))
		data->exit_stat = export(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "unset"))
		data->exit_stat = unset(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "echo"))
		data->exit_stat = my_echo(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "pwd"))
		data->exit_stat = my_pwd(data, data->lst_cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		my_env(data, data->lst_cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		data->exit_stat = my_exit(data, cmd_lst);
		if (data->exit_stat != 1)
			exit(data->exit_stat);
	}
	else
		return (NO_BUILT);
	return (data->exit_stat);
}

int	nofork_list(t_data *data, t_cmd *cmd)
{
	data->fork_flag = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		data->exit_stat = my_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && !cmd->next)
		data->exit_stat = export(data, cmd);
	else if ((!ft_strcmp(cmd->cmd[0], "env") || !ft_strcmp(cmd->cmd[0],
				"/usr/bin/env")) && !cmd->next)
		my_env(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && !cmd->next)
		data->exit_stat = unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit") && !cmd->next)
	{
		if (cmd->prev)
			return (0);
		data->exit_stat = my_exit(data, cmd);
		if (data->exit_stat != 1)
			exit(data->exit_stat);
	}
	else
		data->fork_flag = 1;
	return (data->exit_stat);
}

int	check_nonfork(t_data *data, t_cmd *cmd)
{
	data->fork_flag = 0;
	if (cmd->her_doc_num && heredoc_exec(data, cmd))
	{
		if (cmd->her_in)
		{
			close(cmd->her_in);
			data->fork_flag = 1;
		}
	}
	if (cmd->cmd[0])
		return (nofork_list(data, cmd));
	return (data->exit_stat);
}

int	check_fork(int *pid, t_data *data)
{
	int	i;

	i = 0;
	if (*pid != 0 && data->fork_flag)
	{
		*pid = fork();
		if (*pid < 0)
			perror("fork() error");
		i++;
	}
	return (i);
}
