/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:15:29 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/23 16:38:26 by ssabbaji         ###   ########.fr       */
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

int	heredoc_exec(t_data *data, t_cmd *cmd_lst, int idx)
{
	int		pid;
	t_cmd	*cmd;

	cmd = cmd_lst;
	g_where_ami = 0;
	pid = fork();
	if (pid == 0)
	{
		rl_catch_signals = 1;
		check_delims(data, cmd, idx);
		close(cmd->fd_in);
		close(cmd->her_in);
		close_fds(cmd);
		close_pipes(data->pipes, data->general.count);
		exit(0);
	}
	waitpid(pid, 0, 0);
	kill(pid, SIGKILL);
	return (1);
}
