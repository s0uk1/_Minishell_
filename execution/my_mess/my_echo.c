/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:42:26 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/17 18:54:50 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_rest(char **cmd, int i, int flag)
{
	char	*echo;

	if (flag)
	{
		echo = join_cmd(cmd, count_cmds(cmd), 1);
		echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
		printf("%s", echo);
		printf("\n");
	}
	if (!flag)
	{
		echo = join_cmd(cmd, count_cmds(cmd), i);
		echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
		printf("%s", echo);
	}
}

int	start_index(char **cmd)
{
	int	i;
	int	idx;

	idx = 0;
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			if (!check_valid(cmd[i]))
			{
				idx = i;
				break ;
			}
		}
		idx = i;
		i++;
	}
	return (idx);
}

int	my_echo(t_data *data, t_cmd *cmd_lst)
{
	char	**cmd;
	int		idx;

	cmd = cmd_lst->cmd;
	if (!cmd[1])
		printf("\n");
	if (cmd[1][0] != '-' && cmd[1][1] != 'n')
	{
		print_rest(cmd, 0, 1);
		return (0);
	}
	idx = start_index(cmd);
	print_rest(cmd, idx, 0);
	return (0);
}
