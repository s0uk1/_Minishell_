/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:10:42 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/23 15:06:05 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../debug.h"
#include <string.h>

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
	while (lst)
	{
		if (lst->value)
			printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
		else
			printf("declare -x %s\n", lst->name);
		
		lst = lst->next;
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

t_env	*add_new_env(char **cmd, t_env **lst)
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
		lst_add(lst,new);
		// print_env(*lst);
	}
	else
	{
		//substr fixed export maybe strdup too
		//new->name = ft_substr(cmd[1], 0, ft_strlen(cmd[1]));
		new->name = strdup(cmd[1]);
		new->value = NULL;
		
		lst_add(lst, new);
		new->next = NULL;
		// print_env(*lst);
	}
	return (*lst);
}

t_data	*my_export(t_data *data, t_cmd *lst_cmd)
{
	char    **cmd;
	char	**spl_res;
	t_env	**lst   ;
    t_env 	*new;

	cmd = data->lst_cmd->cmd;
	*lst = data->lst_env;
	
    if (lst)
	{
		if ((ft_strcmp(cmd[0], "export") == 0 ) && !cmd[1])
		{
			sort_env(data);
			print_env(*lst);
		}
		else if ((ft_strcmp(cmd[0], "export") == 0) && cmd[1])
		{
			printf("added env var\n");
			add_new_env(cmd, lst);
		}
	}
	return (data);
}

void	my_unset(t_data *data, t_cmd *lst_cmd)
{
	char	**cmd;
	t_env	*lst;
	t_env	*tmp;
	t_env	*last;

	cmd = data->lst_cmd->cmd;
	lst = data->lst_env;
	if (lst)
	{
		if ((ft_strcmp(cmd[0], "unset") == 0) && cmd[1])
		{
			while (lst && ft_strcmp(lst->name, cmd[1]))
				lst = lst->next;
			if (lst)
			{
				if (lst->next)
					lst->next->prev = lst->prev;
				if (lst->prev)
					lst->prev->next = lst->next;
				free(lst->name);
				free(lst->value);
				free(lst);				
			}
		}
	}
}

void	my_pwd(t_data *data, t_cmd *lst_cmd)
{
	char	*pwd;
	char	**cmd;

	cmd = data->lst_cmd->cmd;
	pwd = getcwd(NULL, 0);
	// perror("getcwd() error"); is useless(?)
	//might also try with getenv("PWD")
	// pwd = getenv("PWD");
	// if (ft_strcmp(cmd[0], "pwd") == 0)
		printf("%s\n", pwd);
}



void	ft_builtins(t_data *data, t_cmd *lst_cmd)
{
	if (ft_strcmp(lst_cmd->cmd[0], "export") == 0)
		my_export(data, lst_cmd);
	else if (ft_strcmp(lst_cmd->cmd[0], "pwd") == 0)
		my_pwd(data, lst_cmd);
	else if (ft_strcmp(lst_cmd->cmd[0], "unset") == 0)
		unset(data, lst_cmd);
	else if (ft_strcmp(lst_cmd->cmd[0], "cd") == 0)
		my_cd(data, lst_cmd);
	else 
		execution_2(data);
}
