/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:53:10 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/20 15:57:32 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define TERM_OWNER 130

int	wait_p(pid_t *p, int *status)
{
	*p = wait(status);
	return (*p);
}

int	terminate_pid(int count)
{
	pid_t	p;
	int		status;
	int		res;

	p = 0;
	while (count)
	{
		while (wait_p(&p, &status) > 0)
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
	close_all(cmd, data->pipes, data->general.count);
	data->exit_stat = check_builtins(data, cmd);
	if (data->exit_stat == NO_BUILT)
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
	data->general.count = c_lstcmd(data);
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
	close_all(data->lst_cmd, data->pipes, data->general.count);
	if (fork_c)
		data->exit_stat = terminate_pid(fork_c);
	printf("|||%d|||\n", fork_c);
	return (data->exit_stat);
}

int	pre_execution(t_data *data)
{
	int		pid;

	pid = 0;
	data->paths = ft_split(custom_getenv("PATH", data->lst_env), ':');
	if (data->lst_cmd)
	{
		data->pipes = initialize_pipes(data);
		execution(data);
	}
	return (0);
}
