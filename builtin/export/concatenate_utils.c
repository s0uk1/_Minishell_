/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:50:50 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/01 13:03:47 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_concate(char *name)
{
	char	*temp;

	if (name[ft_strlen(name) - 1] == '+')
	{
		temp = ft_substr(name, 0, ft_strlen(name) - 1);
		free(name);
		name = ft_strdup(temp);
		free(temp);
		return (1);
	}
	return (0);
}

void	ft_concatenate(t_data *data, char *name, char *value)
{
	char    *temp;
	t_env   *env_clone;

	env_clone = data->lst_env;
	if (ft_name_exists(data, name))
	{
		while (env_clone)
		{
			if (!ft_strcmp(env_clone->name, name))
			{
				temp = env_clone->value;
				if (env_clone->value)
					free(env_clone->value);
				env_clone->value = ft_strjoin(temp, value);
				break ;
			}
			env_clone = env_clone->next;
		}
	}
	else
	{
		ft_add_new_env(data, name, value);
		if (!data->first_export)
			data->first_export = ft_substr(name, 0, ft_strlen(name));
		free(name);
		exit(1);
		if (value)
			free(value);
	}
}
