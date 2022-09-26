/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:52:05 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/26 19:00:53 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	res;

	i = 0;
	res = 0;
	n = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * n);
}

int	ft_isdigit(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_long(char	*cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char *) * 19);
	str = ft_strdup("9223372036854775807");
	if (strlen(cmd) == 19)
	{
		while(str[i])
		{
			if(str[i] == cmd[i])
				i++;
			else 
				return (0);
			if (i == 19)
				return (1);
		}
		if(!ft_strcmp(cmd, str) || ft_strcmp(cmd, str) > 0)
		{
			free(str);
			return (1);
		}
	}
	else
		return (0);
}

int	my_exit(t_cmd *lst_cmd, int old_error)
{
	char	**cmd;
	int		exit_stat;

	exit_stat = g_vars.g_exit_stat;
	cmd = lst_cmd->cmd;
	printf("exit\n");
	if (cmd[1])
	{
		if (cmd[2])
			return (printf("bash: exit: too many arguments\n"), 1);
		else if (ft_isdigit(cmd[1]))
		{
			if (is_long(cmd[1]))
			{
				printf("bash: exit: %s :numeric argument required\n", cmd[1]);
				exit_stat = 255;
			}
			else 
				exit_stat = ft_atoi(cmd[1]);	
		}
		else 
		{
			printf("bash: exit: %s :numeric argument required\n", cmd[1]);
			exit_stat = 255;
		}
	}
	else
		exit(old_error);
	exit (exit_stat);
}
