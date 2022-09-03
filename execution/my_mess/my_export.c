/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:10:42 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/03 14:12:30 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../debug.h"

t_env *lst_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lst_add(t_env	**lst, t_env *new)
{ 
	t_env *last;

	if (lst == NULL || new == NULL)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = lst_last(*lst);
	last->next = new;
}

void    ft_swap_env(t_env *a, t_env *b)
{
    char    *tmp;

    tmp = a->name;
    a->name = b->name;
    b->name = tmp;
    tmp = a->value;
    a->value = b->value;
    b->value = tmp;
}

void	print_env(t_env *lst)
{
	t_env *clone;

	clone = lst;
	while (clone)
	{
		if (clone->name && clone->value)
			printf("declare -x %s=\"%s\"\n", clone->name, clone->value);
		else if (clone->name)
			printf("declare -x %s\n", clone->name);
		clone = clone->next;
	}
}

void    sort_env(t_data *data)
{
    t_env *lst;

    lst = data->lst_env;
    while (lst)
    {
        if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
        {
            ft_swap_env(lst, lst->next);
            lst = data->lst_env;
        }
        else
            lst = lst->next;
    }
}

char *ft_strdup(char *src)
{
	int i = 0;
	int len;
	char *copy;
	
	len = ft_strlen(src);
	copy = (char*)malloc(sizeof(char) * len + 1);
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_env	*add_new_env(char **cmd, t_env *lst)
{
	t_env	*new;
	char	**spl_res;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	if (ft_strchr(cmd[1], '='))
	{
		spl_res= ft_split(cmd[1] , '=');
		new->name = spl_res[0];
		new->value = spl_res[1];
		lst_add(&lst,new);
	}
	else
	{
		//strdup fixed my export for some reason
		new->name = ft_strdup(cmd[1]);
		new->value = NULL;
		lst_add(&lst, new);
		new->next = NULL;
	}
	return (lst);
}

t_data	*my_export(t_data *data, t_cmd *lst_cmd)
{
	char    **cmd;
	char	**spl_res;
	t_env	*lst;
    t_env 	*new;

	cmd = lst_cmd->cmd;
	lst = data->lst_env;
    if (lst)
	{
		if (!cmd[1])
		{
			//sort_env(data);
			print_env(data->lst_env);
		}
		else if (cmd[1])
			add_new_env(cmd, lst);
	}
	return (data);
}

void	my_unset(t_data *data, t_cmd *lst_cmd)
{
	int		i;
	char	**cmd;
	t_env	*lst;
	t_env	*tmp;
	t_env	*last;

	i = 1;
	cmd = lst_cmd->cmd;
	lst = data->lst_env;
	while (lst)
	{
		if(ft_strcmp(lst->name, cmd[i]))
		{
			if (lst->next)
				lst->next->prev = lst->prev;
			if (lst->prev)
				lst->prev->next = lst->next;
			i++;
			free(lst->name);
			free(lst->value);
			free(lst);
			if (!cmd[i])
				break ;
		}
		if (lst)
			lst = lst->next;
	}
}