/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by rsaf              #+#    #+#             */
/*   Updated: 2022/09/03 18:02:26 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	nofork_list(t_data *data, t_cmd *cmd)
{
	data->fork_flag = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		data->exit_stat = my_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && !cmd->next)
		data->exit_stat = export(data, cmd, 1);
		// data = my_export(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env") && !cmd->next)
		my_env(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && !cmd->next)
		data->exit_stat = unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit") && !cmd->next)
	{
		data->exit_stat = my_exit(data, cmd);
		if (data->exit_stat != 1)
			exit(data->exit_stat);
	}
	else
		data->fork_flag = 1;
	return (data->exit_stat);
}

int	check_delim_idx(t_cmd *cmd)
{
	int		delim_idx;
	
	delim_idx = 0;
	if (cmd->prev)
		delim_idx += cmd->prev->her_doc_num;
	return (delim_idx);
}

//exheredoc is to be made

int	check_nonfork(t_data *data, t_cmd *cmd)
{
	int		delim_idx;
	
	data->fork_flag = 0;
	delim_idx = check_delim_idx(cmd);
	if (cmd->her_doc_num > 0 && ft_herdoc(data, cmd, data->pipes, delim_idx))
	{
		if (cmd->her_in)
		{
			close(cmd->her_in);
			data->fork_flag = 1;	
		}
	}
	if(cmd->cmd[0])
		return (nofork_list(data, cmd));
	return (data->exit_stat);
}

int	check_builtins(t_data *data, t_cmd *cmd_lst)
{
	//echo pwd , unset, export , env , exit
	char **cmd;

	cmd = cmd_lst->cmd;
	if (!ft_strcmp(cmd[0], "export"))
		data->exit_stat = export(data, cmd_lst, 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		data->exit_stat = unset(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "echo"))
		my_echo(data, cmd_lst);
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

// int	terminate_pid(int	count)
// {
// 	pid_t	p;
// 	int		status;
// 	int		res;
	
// 	while(count)
// 	{
// 		while ((p = wait(&status) > 0))
// 		{
// 			if(WIFEXITED(status))
// 			{
// 				res = kill(p, SIGKILL);
// 				// if (res < 0)
// 				// 	perror("kill()error:");
// 				// else
// 					return (WIFEXITED(status));
// 			}
// 			else
// 				perror("minishell kill error");
// 		}
// 		count--;
// 	}
// 	return (WIFEXITED(status));
// }


int	ft_wait_nd_kill(int idx)
{
	int	pid;
	int	status;

	while (idx > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) == 0)
			return (130);
		if (WIFEXITED(status) && WEXITSTATUS(status) != -1 && pid != -1)
			kill(pid, SIGKILL);
		idx--;
	}
	return (WEXITSTATUS(status));
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
		data->exit_stat = check_nonfork(data, cmd);
		if (pid != 0 && data->fork_flag)
		{
			pid = fork();
			if (pid < 0)
				perror("fork failed");
			fork_c++;
		}
		if (pid == 0 && cmd->fd_in != -69)
		{
			dup2(cmd->fd_in, 0);
			dup2(cmd->fd_out, 1);
			close_all(cmd , data->pipes, c_lstcmd(data));
			data->exit_stat = check_builtins(data, cmd);
			if(data->exit_stat == -42)
				execution_2(data, cmd);
			exit(1);
		}
		cmd = cmd->next;	
	}
	close_all(data->lst_cmd, data->pipes, c_lstcmd(data));
	if (fork_c)
		// data->exit_stat = terminate_pid(fork_c);
		data->exit_stat = ft_wait_nd_kill(fork_c);
	return (data->exit_stat);
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
