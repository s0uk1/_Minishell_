/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/24 18:43:09 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../debug.h"

// what i need in cd is 
// updating PWD var whenever i change the directory
// in the case of nested directories , if i cd to the last one 
// then delete one of the previous ones i have to implement 
// a workaround to avoid painful segfauls


void    my_cd(t_data *data, t_cmd *lst_cmd)
{
    
    char **cmd;
    cmd = lst_cmd->cmd;
    if (cmd[1])
    {
        if (chdir(cmd[1]))
            perror("chdir() error:");
        // else
        //     update_env("PWD");
    }
}