/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:15:29 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/28 10:47:02 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_delim_idx(t_data *data, t_cmd *cmd)
{
	if (cmd->prev)
		data->general.index += cmd->prev->her_doc_num;
	return (data->general.index);
}

void	print_her_in(t_cmd *cmd, char *here_buff)
{
	ft_putstr_fd(here_buff, cmd->her_in);
	ft_putstr_fd("\n", cmd->her_in);
}

void	check_delims(t_data *data, t_cmd *cmd, int idx)
{
	char	*here_buff;
	int		i;

	i = 0;
	while (1 && i < cmd->her_doc_num)
	{
		here_buff = readline("> ");
		if (here_buff == NULL)
			exit(1);
		if (here_buff[0] != '\0' && !ft_strcmp(data->eof[idx], here_buff))
		{
			i++;
			idx++;
		}
		else
			print_her_in(cmd, here_buff);
	}
}

void	hand(int num)
{
	if (num == SIGINT)
	{
		exit(100);
	}
}



int	heredoc_exec(t_data *data, t_cmd *cmd_lst, int idx)
{
	int		pid;
	int		status;
	t_cmd	*cmd;

	cmd = cmd_lst;
	g_vars.g_where_ami = 0;
	g_vars.g_is_heredoc = 1;
	g_vars.cmd = cmd;
	g_vars.g_her_in = cmd->her_in;
	g_vars.data = data;
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		rl_clear_signals();
		g_vars.g_has_child = 1;
		signal(SIGINT, &hand);
		check_delims(data, cmd, idx);
		close(cmd->fd_in);
		close(cmd->her_in);
		close_fds(cmd);
		close_pipes(data->pipes, data->general.count);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (ft_statushundling(status) == 100)
	{
	// 	// 		close(cmd->fd_in);
	// 	// close_fds(cmd);
	// 	close_pipes(data->pipes, data->general.count);
	// 	// write(1 ,"\n", 1);
	// 	// rl_replace_line("", 0);
	// 	// rl_on_new_line(); 
    // 	// rl_redisplay();
		g_vars.g_exit_stat  = 9;
	// 	// dup2(0, in);
		return (0);
	}
	return (1);
}
