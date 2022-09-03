/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:10:11 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/03 18:29:09 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_access(t_data *data, char **cmd, int i, int flag)
{
	char	*path = NULL;
	int		fd;

	fd = 0;
	if (!flag)
	{
		path = ft_strjoin(data->paths[i], "/");
		path = ft_strjoin(path, cmd[0]);
	}
	else
		path = ft_strjoin(path, cmd[0]);
	fd = access(path, F_OK | X_OK);
		//the reason i didnt use perror here is because
		//it returns an error every single time
	if (fd == -1)
		return (0);
	else
	{
		execve(path, cmd, data->env);
		perror("execve() error");
	}
    return (1);
}

//this function executes commands that arent builtin lmao
void	execution_2(t_data *data , t_cmd *lst_cmd)
{
	int	i;
    int ret;
	char	**cmd;
	t_env	*lst_env;

	i = -1;
	ret = 0;
    data->paths = NULL;
	cmd = lst_cmd->cmd;
	lst_env = data->lst_env;
	
	if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)
		perror("getcwd() error");
	//checking if the command entered is an absolute path (can be an executable to check directly)
	if (cmd[0][0] == '/')
		check_access(data,cmd,0,1);
	while (lst_env && lst_env->name)
	{
		if (ft_strcmp(lst_env->name, "PATH") == 0)
		{
			//for the case when the PATH is unset 
			//rsaf says that if i unset PATH manually then readd it the next if can then be useful
			if(lst_env->value == NULL)
				check_access(data,cmd, i, 0);
			else
			{		
    	        data->paths = ft_split(lst_env->value,':');
    	         while (data->paths[++i] && ret != 1)
					ret = check_access(data, cmd, i, 0);
			}
    	    if (ret == 0)
    	    {
    	        perror("access() error");
    	        break ;
    	    }
		}
		lst_env = lst_env->next;
	}
	// free(data);
}