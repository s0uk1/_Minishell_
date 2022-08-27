/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:42:26 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/27 18:36:27 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"




char **find_flag(char **cmd)
{
    char **flags;
    int i;
    int j;

    i = 0;
    j = 0;
    cmd = lst_cmd->cmd;
    flags = (char *)malloc(sizeof(char *) * count_cmds(cmd) + 1);
    while (cmd[i])
    {
        if (ft_strchr(cmd[i], '-'))
        {
            flags[j] = cmd[i];
            j++;
        }
        i++;
    }
    flags[j] = NULL;
    return (flags);
}

void    my_echo(t_data *data ,t_cmd *lst_cmd)
{
    char **cmd;
    char **flags;
    int i;
    int j;

    i = 0;
    j = 0;
    cmd = lst_cmd->cmd;
    flags = find_flag(cmd);
}


