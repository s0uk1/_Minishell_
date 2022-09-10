/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:14:19 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/07 15:09:03 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	her_finished(t_data *data, t_cmd *cmd_clone, int **pip)
{
	close(cmd_clone->fd_in);
	close(cmd_clone->her_in);
	// close_fds(cmd_clone);
	// close_pipes(pip, data->general.lent);
	exit(0);
}

void	print_for_her(t_cmd *cmd_clone, char *buff)
{
	ft_putstr_fd(buff, cmd_clone->her_in);
	ft_putstr_fd("\n", cmd_clone->her_in);
}

void	herdoc_routine(t_data *data, t_cmd *cmd_lst, int i)
{
	char	*buff;
	int		idx;
	

	
	idx = 0; 
	// loop index that increments to n number of
	//heredocs in a command
	//i is the index of EOF
	while (1 && idx < cmd_lst->her_doc_num)
	{
		buff = readline("heredoc> ");
		if (buff == NULL)
			break ;
		else if (buff[0] != '\0' && !ft_strcmp(buff, data->eof[i]))
		{
			i++;
			idx++;
		}
		else
			print_for_her(cmd_lst, buff);
	}
}

int	ft_herdoc(t_data *data, t_cmd *cmd_lst, int **pip, int i)
{
	//i here is the delimeter of the eof we should start from
		
	
	
	int		pid;
	char	*buff;
	t_cmd	*cmd_clone;
	int		idx;

	//i here is delim_idx for me
	idx = 0;
	cmd_clone = cmd_lst;
	g_where_ami = 0;
	pid = fork();
	if (cmd_clone->her_doc_num && pid == 0)
	{
		// rl_catch_signals = 1;
		herdoc_routine(data, cmd_clone, i);
		her_finished(data, cmd_clone, pip);
	}
	waitpid(pid, 0, 0);
	kill(pid, SIGKILL);
	return (1);
}
