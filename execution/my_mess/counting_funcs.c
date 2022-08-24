/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:48:15 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/24 16:12:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_cmds(t_data *data)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = data->lst_cmd;
	while (tmp)
	{
		if (tmp->cmd)
			i++;
		tmp = tmp->next;
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
