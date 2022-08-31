/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:12:33 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/31 15:25:04 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int **alloc_pipes(t_data *data)
{
    int *fd[2];
    int c;
    int i;

    i = 0;
    c = c_lstcmd(data);
    fd = (int *)malloc(sizeof(int) * (c - 1));
    if (!fd)
        return (NULL);
    while (i < c - 1)
    {
        fd[i] = malloc(sizeof(int * 2));
        if (!fd[i])
            return (NULL);
        i++;
    }
    while (i < c - 1)
    {
        pipe(fd[i]);
        i++;
    }
    return (fd);
}

void    init_fd(int **fd, t_cmd *cmd, int i)
{

    if (i == 0 && cmd->next)
        if (out == 1)
            cmd->fd_out = fd[i][1];
    else if (i != 0 && cmd->next)
    {
        if (in == 0)
            cmd->fd_in = fd[i - 1][0];
        if (out == 1)
            cmd->fd_out = fd[i][1];       
    }
    else if (i != 0 && !cmd->next)
        if (in == 0)
            cmd->fd_in = fd[i - 1][0];
    return (i);
}

int **initialize_pipes(t_data *data)
{
    int     **fd;
    t_cmd   *cmd;
    
    fd = alloc_pipes(data);
    //add the lst_cmd protection beforehand
    while (cmd)
    {
        init_fd(fd, cmd, i);
    }
    
}