/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by rsaf              #+#    #+#             */
/*   Updated: 2022/09/02 18:50:05 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	nofork_list(t_data *data, t_cmd *cmd)
{
	data->fork_flag = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		data->error = cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && !cmd->next)
		data->error = export(data, cmd, 1);
	else if (!ft_strcmp(cmd->cmd[0], "env") && !cmd->next)
		data->error = ft_env_built(data, cmd->fd_out);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && !cmd->next)
		data->error = unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit") && !cmd->next)
	{
		data->error = ft_exit(data, cmd, 1);
		if (data->error != 1)
			exit(data->error);
	}
	else
		data->fork_flag = 1;
	return (data->error);
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
	if (cmd->her_doc_num > 0 && ex_heredoc(data, cmd,delim_idx))
	{
		if (cmd->her_in)
		{
			close(cmd->her_in);
			data->fork_flag = 1;	
		}
	}
	if(cmd->cmd[0])
		return (nofork_list(data, cmd));
	return (data->error);
}

// non fork funcs are the ones that change the env
// therefore they dont need to be forked for 
// gotta check the heredoc and execute it
// void	fork_func(t_data *data)
// {
// 	t_cmd	*cmd;
// 	int		pid;
	
// 	cmd = data->lst_cmd;
// 	pid = 66;
// 	while(cmd)
// 	{
// 		if (pid != 0)
// 		{
// 			pid = fork();
// 		}
// 		if(pid == 0)
// 		{
// 			dup2(cmd->fd_in, 0);
// 			dup2(cmd->fd_out, 1);
// 			close_fds(cmd);
// 			close_pipes(data->pipes, c_lstcmd(data));
// 			execut 
// 			exit(1);
// 		}
// 		cmd = cmd->next;
// 	}
// 	close_fds(cmd);
// 	close_pipes(data->pipes, c_lstcmd(data));
// 	int i = -1;
// 	while (++i < c_lstcmd(data))
// 		waitpid(-1, 0, 0);
// }


int	check_builtins(t_data *data, t_cmd *cmd_lst)
{
	//echo pwd , unset, export , env , exit
	char **cmd;

	cmd = cmd_lst->cmd;
	if (!ft_strcmp(cmd[0], "export"))
		data->error = export(data, cmd_lst, 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		data->error = unset(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "echo"))
		my_echo(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "env"))
		my_env(data, data->lst_cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		data->error = my_exit(data, cmd_lst);
		if (data->error != 1)
			exit(data->error);
	}
	else
		return (-42);
	return (data->error);
}

int	terminate_pid(int	count)
{
	pid_t	p;
	int		status;
	int		res;
	
	while(count)
	{
		while ((p = wait(&status) > 0))
		{
			if(WIFEXITED(status))
			{
				res = kill(p, SIGKILL);
				if (res < 0)
					perror("kill()error:");
				else
					return (WIFEXITED(status));
			}
			else
				perror("minishell kill error");
		}
		count--;
	}
	return (WIFEXITED(status));
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
		data->error = check_nonfork(data, cmd);
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
			data->error = check_builtins(data, cmd);
			if(data->error == -42)
				execution_2(data, cmd);
			exit(1);
		}
		cmd = cmd->next;	
	}
	close_all(data->lst_cmd, data->pipes, c_lstcmd(data));
	if (fork_c)
		data->error = terminate_pid(fork_c);
	return (data->error);
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
