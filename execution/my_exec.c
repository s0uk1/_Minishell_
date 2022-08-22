/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:10:11 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/10 11:10:12 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_access(t_data *data, char **cmd, int i)
{
	char	*path = NULL;
	int		fd;

	fd = 0;
	path = ft_strjoin(data->paths[i], "/");
	path = ft_strjoin(path, cmd[0]);
	fd = access(path, F_OK);
	if (fd == -1)
		return (0);
	else
	{
		execve(path, cmd, data->env);
		perror("execve() error");
	}
    return (1);
}

void	execution_2(t_data *data)
{
	int	i;
    int ret;
	char	**cmd;
	t_env	*lst_env;

	i = -1;
	ret = 0;
    data->paths = NULL;
	cmd = data->lst_cmd->cmd;
	lst_env = data->lst_env;
	if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)
		perror("getcwd() error");
	if (cmd[0][0] == '/')
		check_access(data,NULL,0);
	while (lst_env && lst_env->name)
	{
		if (ft_strcmp(lst_env->name, "PATH") == 0)
		{
			if(lst_env->value == NULL)
				check_access(data,cmd, i);
			else
			{		
                data->paths = ft_split(lst_env->value,':');
                while (data->paths[++i] && ret != 1)
					ret = check_access(data, cmd, i);
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