/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:53:10 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/15 16:42:30 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define TERM_OWNER 130

int	check_builtins(t_data *data, t_cmd *cmd_lst)
{
	char	**cmd;

	cmd = cmd_lst->cmd;
	if (!ft_strcmp(cmd[0], "export"))
		data->exit_stat = export(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "unset"))
		data->exit_stat = unset(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "echo"))
		my_echo(data, cmd_lst);
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
		return (-42);
	return (data->exit_stat);
}
int		wait_p(pid_t *p, int *status)
{
	p = wait(&status);
	return (p);
}

int	terminate_pid(int count)
{
	pid_t	p;
	int		status;
	int		res;

	p = 0;
	while (count)
	{
		while (wait_p(&p , &status) > 0)
		{
			if (WIFEXITED(status))
				res = kill(p, SIGKILL);
			else
				return (TERM_OWNER);
		}
		count--;
	}
	return (WEXITSTATUS(status));
}

int	dup_and_close(t_data *data, t_cmd *cmd)
{
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	close_all(cmd, data->pipes, c_lstcmd(data));
	data->exit_stat = check_builtins(data, cmd);
	if (data->exit_stat == -42)
		data->exit_stat = execution_2(data, cmd);
	return (data->exit_stat);
}

int	execution(t_data *data)
{
	t_cmd	*cmd;
	int		pid;
	int		fork_c;

	cmd = data->lst_cmd;
	fork_c = 0;
	while (cmd)
	{
		data->exit_stat = check_nonfork(data, cmd);
		fork_c = check_fork(&pid, data);
		if (pid == 0 && !data->rerror_f)
		{
			g_where_ami = 0;
			data->exit_stat = dup_and_close(data, cmd);
			exit(data->exit_stat);
		}
		cmd = cmd->next;
	}
	close_all(data->lst_cmd, data->pipes, c_lstcmd(data));
	if (fork_c)
		data->exit_stat = terminate_pid(fork_c);
	return (data->exit_stat);
}

int	pre_execution(t_data *data)
{
	int		pid;
	t_cmd	*cmd;

	pid = 0;
	data->paths = ft_split(custom_getenv("PATH", data->lst_env), ':');
	if (data->lst_cmd)
	{
		data->pipes = initialize_pipes(data);
		execution(data);
	}
	return (0);
}
