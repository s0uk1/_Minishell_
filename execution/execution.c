/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:53:10 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/30 16:58:06 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define TERM_OWNER 130

int	wait_p(pid_t *p, int *status)
{
	*p = wait(status);
	return (*p);
}

int	ft_statushundling(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(2, "Quit: 3\n", 8);
		if (WTERMSIG(status) == 2)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	terminate_pid(pid_t lastchild)
{
	int	status;

	waitpid(lastchild, &status, 0);
	while (wait(NULL) != -1)
		;
	return (ft_statushundling(status));
}

int	dup_and_close(t_data *data, t_cmd *cmd)
{
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	close_fds(cmd);
	close_pipes(data->pipes, data->general.count);
	g_vars.g_exit_stat = check_builtins(data, cmd);
	if (g_vars.g_exit_stat == NO_BUILT)
		g_vars.g_exit_stat = execution_2(data, cmd);
	return (g_vars.g_exit_stat);
}

int	execution(t_data *data)
{
	t_cmd	*cmd;
	int		pid;
	int		fork_c;

	cmd = data->lst_cmd;
	fork_c = 0;
	pid = 1;
	data->general.count = c_lstcmd(data);
	while (cmd)
	{
		g_vars.g_exit_stat = check_nonfork(data, cmd);
		if (g_vars.g_heredoc == 0)
			return (HEREDOC_EXE);
		fork_c += check_fork(&pid, data);
		if (pid == 0 && !data->rerror_f)
		{
			g_vars.g_where_ami = 0;
			g_vars.g_exit_stat = dup_and_close(data, cmd);
			exit(g_vars.g_exit_stat);
		}
		cmd = cmd->next;
	}
	close_all(data->lst_cmd, data->pipes, data->general.count);
	if (fork_c)
		g_vars.g_exit_stat = terminate_pid(pid);
	return (g_vars.g_exit_stat);
}

int	pre_execution(t_data *data)
{
	int	pid;

	pid = 0;
	if (data->lst_cmd)
	{
		data->pipes = initialize_pipes(data);
		if (execution(data) == HEREDOC_EXE)
			g_vars.g_exit_stat = 1;
	}
	return (0);
}
