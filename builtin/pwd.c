/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:46:44 by rsaf              #+#    #+#             */
/*   Updated: 2022/08/24 18:04:14 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_data *data, t_cmd *lst_cmd, int fd)
{
	char	*curr_wd;

	curr_wd = NULL;
	if (lst_cmd)
	{
		if (lst_cmd->cmd[0])
		{
			curr_wd = getcwd(curr_wd, 0);
			if (!curr_wd)
				ft_putstr_fd(ft_get_env(data, "PWD"), 1);
			else
				ft_putstr_fd(curr_wd, fd);
			write(fd, "\n", 1);
		}
		else
			return (printf("pwd: too many arguments\n"), 1);
	}
	return (0);
}

// change the PWD : /Users/rsaf/Desktop/2.0shell/t1/t2/..
// and OLD PWD to : /Users/rsaf/Desktop/2.0shell/t1/t2

//the following function is a reentrant version of the getenv() function in c

char *custom_getenv(char *env_var, t_env *env_lst)
{
	t_env *tmp;
	char *pwd;
	
	tmp = env_lst;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, env_var))
			pwd = tmp->name;
		else
			tmp = tmp->next;
	}
	return (pwd);
}

void	my_pwd(t_data *data, t_cmd *lst_cmd)
{
	char	*cwd;
	//char	**cmd;
	
	//useless var and init ???
	//cmd = data->lst_cmd->cmd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		cwd = custom_getenv("PWD", data->lst_env);		
	printf("%s\n", cwd);
		// perror("pwd() error:");
}