/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:42:22 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/05 15:59:13 by ssabbaji         ###   ########.fr       */
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
    if (cmd[1])
    {
        perror("env() error");
        return ;
    }
    while (env)
    {
        if (env->value && ft_strlen(env->value))
            printf("%s=%s\n",env->name, env->value);
        env = env->next;
    }
}