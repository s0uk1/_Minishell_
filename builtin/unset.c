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


void free_env_node(t_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
	}
}

void	ft_my_unset(t_data *data, char **cmd)
{
	int		idx;
	t_env	*env;

	if (!data->lst_env)
		return ;
	if (ft_strcmp(cmd[1], data->lst_env->name) == 0)
	{
		env = data->lst_env;
		data->lst_env = data->lst_env->next;
		free_env_node(env);
		return ;
	}
	idx = 1;
	while (cmd[idx])
	{
		env = data->lst_env;
		while (env)
		{
			if (!ft_strcmp(cmd[idx], env->name))
				break ;
			env = env->next;
		}
		if (!env)
			return ;
		env->prev->next = env->next;
		free_env_node(env);
		idx++;
	}
}

int unset(t_data *data, t_cmd *cmd)
{
	if (!cmd->cmd[1])
		return (1);
	ft_my_unset(data, cmd->cmd);
	return (0);
}