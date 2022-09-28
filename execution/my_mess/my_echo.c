/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:42:26 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/28 11:49:27 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_rest(char **cmd, int i, int flag)
{
	char	*echo;
	char	*free_echo;

	if (flag)
	{
		echo = join_cmd(cmd, count_cmds(cmd), 1);
		free_echo = echo;
		echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
		printf("%s", echo);
		printf("\n");
	}
	if (!flag)
	{
		echo = join_cmd(cmd, count_cmds(cmd), i);
		free_echo = echo;
		echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
		printf("%s", echo);
	}
	free(free_echo);
}

int	start_index(char **cmd)
{
	int	i;
	int	idx;

	idx = 0;
	i = 1;
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] == '-')
		{
			if (!check_valid(cmd[i]))
			{
				idx = i;
				break ;
			}
			else 
				i++;
		}
		else if (!check_valid(cmd[i]))
		{
			idx = i;
			break ;
		}
		idx = i;
		i++;
	}
	printf("%d\n", idx);
	printf("%d\n", i);
	if (cmd[i] == NULL && check_valid(cmd[i - 1]) && check_valid(cmd[i]))
		return (0);
	return (idx);
}


//printf("||||||||");
int	my_echo(t_cmd *cmd_lst)
{
	char	**cmd;
	int		idx;

	cmd = cmd_lst->cmd;
	if (!cmd[1])
	{
		printf("here\n");
		printf("\n");
	}
	if (cmd[1][0] != '-' && cmd[1][1] != 'n')
	{
		printf("1 ||||||||\n");
		print_rest(cmd, 0, 1);
		return (0);
	}
	idx = start_index(cmd);
	printf("%d\n", idx);
	if (idx == 1)
	{
		printf("2 ||||||||\n");
		print_rest(cmd, idx, 1);
	}
	if (idx == 0)
	{
		printf("3 ||||||||\n");
		return (0);
	}
	else
	{
		printf("4 ||||||||\n");
		print_rest(cmd, idx, 0);
	}
	// printf("here\n");
	return (0);
}
