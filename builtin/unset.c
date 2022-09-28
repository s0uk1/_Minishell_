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

#include <stdbool.h>

bool remove_env_node(t_env **venv, char *name)
{
	t_env	*env;

	if (!*venv)
		return false;
	if (ft_strcmp(name, (*venv)->name) == 0)
	{
		env = *venv;
		*venv = (*venv)->next;
		free_env_node(env);
		return true;
	}
	env = *venv;
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			break;
		env = env->next;
	}
	if (!env)
		return false;
	env->prev->next = env->next;
	free_env_node(env);
	return true;
}

void ft_my_unset(t_data *data, char **cmd)
{
	int idx;
	
	idx = 1;
	while (cmd[idx])
	{
		remove_env_node(&data->lst_env, cmd[idx]);
		idx++;
	}
	printf("%p\n", data->lst_env);
}

int unset(t_data *data, t_cmd *cmd)
{
	if (!cmd->cmd[1])
		return (1);
	ft_my_unset(data, cmd->cmd);
	return (0);
}