/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:55:18 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/16 13:57:40 by ssabbaji         ###   ########.fr       */
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

char	*cd_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			exit (1);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		exit (1);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}
