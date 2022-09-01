/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by rsaf              #+#    #+#             */
/*   Updated: 2022/09/01 16:33:34 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//non fork funcs are the ones that change the env
//therefore they dont need to be forked for 
//gotta check the heredoc and execute it
// int	check_delim_idx(t_data *data)
// {
// 	t_cmd	*cmd;
// 	int		delim_idx;
	
// 	delim_idx = 0;
// 	cmd = data->cmd;
// 	if (cmd->prev)
// 		delim_idx += cmd->prev->her_doc_num;
// 	return (delim_idx);
// }

// //exheredoc is to be made

// int	check_nonfork(data)
// {
// 	t_cmd	*cmd;
// 	int		delim_idx;
	
// 	cmd = data->cmd;
// 	delim_idx = check_delim_idx(cmd);
// 	if (cmd->her_doc_num > 0 && ex_heredoc(data, delim_idx))
// 		if (cmd->her_in)
// 			return (close(cmd->her_in), NULL);
// 	if(cmd->cmd[0])
// 		return (ft_builtins(data));
// }

void	fork_func(t_data *data)
{
	t_cmd	*cmd;
	int		pid;
	
	cmd = data->lst_cmd;
	pid = 66;
	while(cmd)
	{
		if (pid != 0)
			pid = fork();
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


// int	execution(t_data *data)
// {
// 	t_cmd	*cmd;

// 	cmd = data->lst_cmd;
// 	while (cmd)
// 	{
// 		data->error = check_nonfork(data);
// 		if (data->error == NULL)
// 		{
			
// 		}
// 		else
// 		{
// 			fork_func(data);
// 		}	
// 	}
// }


int	pre_execution(t_data *data)
{
	int	pid;
	t_cmd *cmd;

	pid = 0;
	data->paths = ft_split(custom_getenv("PATH", data->lst_env),':');
	if (data->lst_cmd)
	{
		data->pipes = initialize_pipes(data);
		ft_print_cmd(data->lst_cmd);
		fork_func(data);
	}
	return (0);
}
