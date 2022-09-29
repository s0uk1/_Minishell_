/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:50:38 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/28 15:14:27 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_valid_(char *cmd)
{
    int i;

    i = 1;
    if(cmd[0] == '-')
    {
        if(!cmd[1])
            return (0);
        while (cmd[i])
        {
            if(cmd[i] != 'n')
			{
				printf("char : %c\n", cmd[i]);
                return (0);
			}
            i++;
        }
    }
    else 
        return (0);
    return (1);
}


int my_echo(t_cmd *cmd_lst)
{
    char    **cmd;
    int     idx;
    int     i;

    i = 0;
    idx = 0;
    cmd = cmd_lst->cmd;
    while(cmd[i])
    {
        if (!check_valid(cmd[i]))
            printf("error here\%s|\n", cmd[i])
        i++;
    }
}