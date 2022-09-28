/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:50:38 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/28 13:01:23 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int check_valid(char **cmd)
{
    int i;

    i = 1;
    if(cmd[0] == '-')
    {
        while (cmd[i])
        {
            if(cmd[i] != 'n')
                return (0);
            i++;
        }
    }
    else 
        return (0);
    return (1);
}

int start_index(char **cmd)
{
    int i;
    int idx;

    i = 0;
    idx = 0;
    while (cmd[i])
    {
        if(!check_valid(cmd[i]))
            idx = i;
        i++;
    }
}

int my_echo(t_cmd *cmd_lst)
{
    char    **cmd;
    int     idx;

    cmd = cmd_lst->cmd;
    if(!cmd[1])
        write(1, "\n", 1);
    if (cmd[1][0] != '-' && cmd[1][1] != 'n')
	{
		print_rest(cmd, 0, 1);
		return (0);
	} 
}