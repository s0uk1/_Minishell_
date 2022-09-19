/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:39 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/19 16:29:50 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_this(t_env *env_clone)
{
	free(env_clone->name);
	free(env_clone->value);
	free(env_clone);
}

// int	valid_name(char *name, t_data **data)
// {
// 	if ((name[0] > 32 && name[0] < 65) || name[0] == '\0')
// 	{
// 		printf("bash: export: `%s': not a valid identifier\n", name);
// 		(*data)->exit_stat = 1;
// 		return (0);
// 	}
// 	return (1);
// }

int	unset(t_data *data, t_cmd *lst_cmd)
{
	int		idx;
	t_env	*env_clone;

	idx = 1;
	env_clone = data->lst_env;
	if (!lst_cmd->cmd[1])
		return (1);
	while (env_clone)
	{
		// valid_name(env_clone->name, &data);
		if (!ft_strcmp(lst_cmd->cmd[idx], env_clone->name))
		{
			if (env_clone->next)
				env_clone->next->prev = env_clone->prev;
			if (env_clone->prev)
				env_clone->prev->next = env_clone->next;
			idx++;
			ft_free_this(env_clone);
			if (!lst_cmd->cmd[idx])
				return (0);
		}
		if (env_clone)
			env_clone = env_clone->next;
	}
	return (0);
}
