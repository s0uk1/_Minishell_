/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:25:24 by yabtaour          #+#    #+#             */
/*   Updated: 2022/08/29 12:51:42 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_norme(t_data *data, t_cmd *lst_cmd, int fd)
{
	if (!lst_cmd->next)
		ft_putstr_fd("exit\n", fd);
	if (lst_cmd->cmd[2])
	{
		ft_putstr_fd("too many arguments\n", fd);
		return (1);
	}
	else
	{
		if (!ft_is_num(lst_cmd->cmd[1]))
		{
			ft_putstr_fd("numeric argument required\n", fd);
			return (255);
		}
		else
			return (ft_atoi(lst_cmd->cmd[1]));
	}
}

int	ft_exit(t_data *data, t_cmd *lst_cmd, int fd)
{
	if (lst_cmd->cmd[0] && lst_cmd->cmd[1])
	{
		return (ft_norme(data, lst_cmd, fd));
	}
	if (lst_cmd->cmd[0] && !lst_cmd->cmd[1])
	{
		if (!lst_cmd->next)
			ft_putstr_fd("exit\n", fd);
		return (0);
	}
	return (0);
}
