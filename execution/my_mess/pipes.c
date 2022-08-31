/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:12:33 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/31 16:46:25 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int **alloc_pipes(t_data *data)
{
    int **fds;
    int c;
    int i;

    i = 0;
    c = c_lstcmd(data);
    fds = (int **)malloc(sizeof(int *) * (c - 1));
    if (!fds)
        return (NULL);
    while (i < c - 1)
    {
        fds[i] = malloc(sizeof(int) * 2);
        if (!fds[i])
            return (NULL);
        i++;
    }
    while (i < c - 1)
    {
        pipe(fds[i]);
        i++;
    }
    return (fds);
}

void    init_fd(int **fd, t_cmd *cmd, int i)
{

    if (i == 0 && cmd->next)
    {
        if (cmd->fd_out == 1)
            cmd->fd_out = fd[i][1];
    }
    else if (i != 0 && cmd->next)
    {
        if (cmd->fd_in == 0)
            cmd->fd_in = fd[i - 1][0];
        if (cmd->fd_out == 1)
            cmd->fd_out = fd[i][1];       
    }
    else if (i != 0 && !cmd->next)
        if (cmd->fd_in == 0)
            cmd->fd_in = fd[i - 1][0];
}

int **initialize_pipes(t_data *data)
{
    int     **fd;
    t_cmd   *cmd;
    int     i;
    
    i = 0;
    fd = alloc_pipes(data);
    cmd = data->lst_cmd;
    //add the lst_cmd protection beforehand
    while (cmd)
    {
        init_fd(fd, cmd, i);
        i++;
        cmd = cmd->next;
        printf("IN %d\n: ", cmd->fd_in);
        printf("OUT %d\n: ", cmd->fd_out);
    }
    return (0);
}