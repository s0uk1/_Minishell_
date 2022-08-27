/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:42:22 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/27 16:38:50 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



//a variable should hava a value in order for it to be
//displayed when the env command is invoked 
void    my_env(t_data *data, t_cmd *lst_cmd)
{
    char **cmd;
    t_env *env;
    
    cmd =lst_cmd->cmd;
    env = data->lst_env;
    while (env)
    {
        if (env->value)
            printf("%s=%s\n",env->name, env->value);
        env = env->next;
    }
}