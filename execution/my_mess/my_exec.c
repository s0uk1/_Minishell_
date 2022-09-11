/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:10:11 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/11 17:54:43 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *generate_path(t_data *data, char **cmd, int i, int flag)
{
	char *path;
	
	path = NULL;
	if (!flag)
	{
		path = ft_strjoin(data->paths[i], "/");
		path = ft_strjoin(path, cmd[0]);
	}
	else if (flag == 1)
		path = ft_strjoin(path, cmd[0]);
	else
	{
		path = ft_strjoin(custom_getenv("PWD", data->lst_env), "/");
		path = ft_strjoin(path, cmd[0]);
	}
	return (path);
}

int	check_access(t_data *data, char **cmd, int i, int flag)
{
	char	*path;
	int		fd;

	fd = 0;
	path = generate_path(data, cmd, i, flag);
	fd = access(path, F_OK | X_OK);
	if (fd == -1)
		return (0);
	else
	{
		execve(path, cmd, data->env);
		perror("execve() error");
		if (errno == EACCES)
			exit(126);
	}
    return (1);
}

int	check_path(t_env *lst_env)
{
	while (lst_env && lst_env->name)
	{
		if (!ft_strcmp(lst_env->name, "PATH"))
			return (1);
		lst_env = lst_env->next;
	}
	return (0);
}

int	check_nonabs(t_data *data, t_cmd *lst_cmd, char **cmd)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	if (check_path(data->lst_env))
	{
    	data->paths = ft_split(custom_getenv("PATH", data->lst_env),':');
    	while (data->paths[++i] && ret != 1)
			ret = check_access(data, cmd, i, 0);
    	if (!ret)
		{
			printf("bash : %s: command not found\n",cmd[0]);
			return (0);
		}
	}
	else
		if(!check_access(data,cmd,0 , 3))
		{
			printf("bash: %s: No such file or directory\n",cmd[0]);
			return (0);	
		}
	return (1);
}

int	execution_2(t_data *data , t_cmd *lst_cmd)
{
	char	**cmd;

    data->paths = NULL;
	cmd = lst_cmd->cmd;
	if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)
		perror("getcwd() error");
	if (cmd[0][0] == '/')
		check_access(data,cmd,0,1);
	if (check_nonabs(data, lst_cmd, cmd))
		data->exit_stat = 0;
	else
		data->exit_stat = 127;
	return (data->exit_stat);
}