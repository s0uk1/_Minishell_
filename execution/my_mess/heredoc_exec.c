/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:15:29 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/07 17:26:38 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_delim_idx(t_cmd *cmd)
{
	int		delim_idx;
	
	delim_idx = 0;
	if (cmd->prev)
		delim_idx += cmd->prev->her_doc_num;
	return (delim_idx);
}

void    print_her_in(t_cmd *cmd, char *here_buff)
{
    ft_putstr_fd(here_buff, cmd->her_in);
    ft_putstr_fd("\n", cmd->her_in);    
}

void    check_delims(t_data *data, t_cmd *cmd)
{
    char    *here_buff;
    int     delim_idx;
    int     i;
    
    delim_idx = check_delim_idx(cmd);
    printf("%d\n",delim_idx);
    while (i < cmd->her_doc_num)
    {
        here_buff = readline("heredoc> ");
        if (here_buff == NULL)
            break ;
        else if(here_buff && !ft_strcmp(data->eof[delim_idx] , here_buff))
        {
            delim_idx++;
            i++;
        }
        else
            print_her_in(cmd, here_buff);
    }
}

 int    heredoc_exec(t_data *data, t_cmd *cmd_lst)
 {
    int     pid;
    t_cmd   *cmd;
    
    g_where_ami = 0;
    pid = fork();
    
    if (pid == 0 && cmd->her_doc_num)
    {
        printf("|||||||||||||||||||||\n");
        check_delims(data , cmd);
        close_all(cmd, data->pipes, count_cmds(cmd->cmd));
        close(cmd->fd_in);
	    close(cmd->her_in);
        exit(0);
    }
    // waitpid(pid, 0, 0);
	// kill(pid, SIGKILL);
    return (1);  
 }