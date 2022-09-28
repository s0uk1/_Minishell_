/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:39 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/27 13:07:31 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void    ft_free_this(t_env *env_clone)
{
    if (env_clone->next)
        env_clone->next->prev = env_clone->prev;
    if (env_clone->prev)
        env_clone->prev->next = env_clone->next;
    free(env_clone->name);
    free(env_clone->value);
    free(env_clone);
}

int    unset_helper(t_env *env_clone, t_data *data, t_cmd *lst_cmd)
{
    int        idx;
    // t_env    *env_clone;

    idx = 1;
    while (lst_cmd->cmd[idx])
    {
        env_clone = data->lst_env;
        while (env_clone)
        {
            if (!ft_strcmp(lst_cmd->cmd[idx], env_clone->name))
            {
                ft_free_this(env_clone);
                break ;
            }
            env_clone = env_clone->next;
        }
        idx++;
    }
    return (0);
}

int    unset(t_data *data, t_cmd *lst_cmd)
{
    t_env    *env_clone;

    env_clone = data->lst_env;
    if (!lst_cmd->cmd[1])
        return (1);
    if (!unset_helper(env_clone, data, lst_cmd))
        return (0);
    else
        return (1);
    return (0);
}

