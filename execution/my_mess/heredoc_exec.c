/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:15:29 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/01 19:32:59 by ssabbaji         ###   ########.fr       */
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

void	hand(int num)
{
	int	fd[2];

	(void)num;
	// rl_done = 1;
	g_vars.g_heredoc = 0;
	pipe(fd);
	dup2(fd[0], 0);
	write(fd[1], "\n", 1);
}

static void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

void	check_delims(t_data *data, t_cmd *cmd, int idx)
{
	char	*here_buff;
	int		i;

	i = 0;
	suppress_output();
	signal(SIGINT, &hand);
	while (g_vars.g_heredoc && i < cmd->her_doc_num)
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
	dup2(cmd->her_in, STDIN_FILENO);
}

int	heredoc_exec(t_data *data, t_cmd *cmd_lst, int idx)
{
	int		tmp;
	t_cmd	*cmd;

	cmd = cmd_lst;
	g_vars.g_where_ami = 0;
	tmp = dup(0);
	g_vars.g_heredoc = 1;
	check_delims(data, cmd, idx);
	close(cmd->fd_in);
	close(cmd->her_in);
	close_fds(cmd);
	dup2(tmp, 0);
	close(tmp);
	return (1);
}
