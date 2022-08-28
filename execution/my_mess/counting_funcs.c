/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:48:15 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/28 13:11:41 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_cmds(char **cmd)
{
	char    **tmp;
	int		i;
    int     j;
	
    i = 0;
    j = 0;
	tmp = cmd;
	while (tmp[i])
	{
		if (tmp)
			i++;
		j++;
	}
	return (i);
}

int     count_pipes(t_data *data)
{
    int i;
    int count;
    char **cmd;

    cmd = data->lst_cmd->cmd;
    i = 0;
    count = 0;
    while (cmd[i])
    {
        if (ft_strcmp(*cmd, "|") == 0)
            count++;
        i++;
    }
    return (count);
}
