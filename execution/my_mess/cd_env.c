/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:55:18 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/15 14:01:02 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*update_env(t_data *data, char *env, char *upd)
{
	t_env	*lst;

	lst = data->lst_env;
	while (lst)
	{
		if (!ft_strcmp(lst->name, env))
		{
			lst->value = ft_strdup(upd);
			return (lst->value);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*custom_getenv(char *env_var, t_env *env_lst)
{
	t_env	*tmp;
	char	*pwd;

	tmp = env_lst;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, env_var))
		{
			pwd = tmp->value;
			break ;
		}
		else
			tmp = tmp->next;
	}
	return (pwd);
}
