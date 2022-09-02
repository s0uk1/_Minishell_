/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by rsaf              #+#    #+#             */
/*   Updated: 2022/09/02 12:04:13 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_delim_idx(t_data *data)
{
	t_cmd	*cmd;
	int		delim_idx;
	
	delim_idx = 0;
	cmd = data->cmd;
	if (cmd->prev)
		delim_idx += cmd->prev->her_doc_num;
	return (delim_idx);
}

//exheredoc is to be made

int	check_nonfork(data)
{
	t_cmd	*cmd;
	int		delim_idx;
	
	cmd = data->cmd;
	delim_idx = check_delim_idx(cmd);
	if (cmd->her_doc_num > 0 && ex_heredoc(data, cmd,delim_idx))
		if (cmd->her_in)
			return (close(cmd->her_in), -666);
	if(cmd->cmd[0])
		return (ft_builtins(data));
}

// non fork funcs are the ones that change the env
// therefore they dont need to be forked for 
// gotta check the heredoc and execute it
void	fork_func(t_data *data)
{
	t_cmd	*cmd;
	int		pid;
	
	cmd = data->lst_cmd;
	pid = 66;
	while(cmd)
	{
		if (pid != 0)
		{
			pid = fork();
		}
		if(pid == 0)
		{
			dup2(cmd->fd_in, 0);
			dup2(cmd->fd_out, 1);
			close_fds(cmd);
			close_pipes(data->pipes, c_lstcmd(data));
			execution_2(data , cmd);
			exit(1);
		}
		cmd = cmd->next;
	}
	close_fds(cmd);
	close_pipes(data->pipes, c_lstcmd(data));
	int i = -1;
	while (++i < c_lstcmd(data))
		waitpid(-1, 0, 0);
}


int	execution(t_data *data)
{
	t_cmd	*cmd;
	int		pid;
	int		fork_c;
	
	cmd = data->lst_cmd;
	pid = 66;
	fork_c = 0;
	while (cmd)
	{
		data->error = check_nonfork(data);
		if (pid != 0 && data->error == -666)
		{
			pid = fork();
			fork_c++:
		}
		if (pid == 0 && cmd->fd_in != -69)
		{
			dup2(cmd->fd_in, 0);
			dup2(cmd->fd_out, 1);
			close_all(cmd , data->pipes, c_lstcmd(data));
			//check builtins here
			executions2(data, cmd);
			exit(1);
		}
		cmd = cmd->next;	
	}
	close_all(data->lst_cmd, data->pipes, c_lstcmd(data));
	if (fork_c)
		//waitpid goes here
}


int	pre_execution(t_data *data)
{
	int	pid;
	t_cmd *cmd;

	pid = 0;
	data->paths = ft_split(custom_getenv("PATH", data->lst_env),':');
	if (data->lst_cmd)
	{
		data->pipes = initialize_pipes(data);
		execution(data);
	}
	return (0);
}
