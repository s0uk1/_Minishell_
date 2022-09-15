/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/15 13:55:46 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_chdir(t_data *data, char *cmd, char *cwd)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (!cmd)
	{
		data->exit_stat = chdir(custom_getenv("HOME", data->lst_env));
		if (data->exit_stat)
			return (perror("chdir() error:"), 1);
	}
	else
	{
		data->exit_stat = chdir(cmd);
		if (data->exit_stat)
			return (perror("chdir() error:"), 1);
		else
		{
			new_pwd = getcwd(NULL, 0);
			update_env(data, "OLDPWD", cwd);
			update_env(data, "PWD", new_pwd);
		}
	}
	return (data->exit_stat);
}

void	find_dir(t_data *data, char *pwd, char *upd)
{
	int		i;
	char	*test_pwd;

	i = 0;
	while (pwd[i])
		i++;
	while (pwd[i] != '/')
		i--;
	test_pwd = ft_strncpy(test_pwd, pwd, i);
	if (chdir(test_pwd))
		find_dir(data, test_pwd, upd);
	else
	{
		printf("%s\n", upd);
		my_chdir(data, test_pwd, upd);
	}
}

int	catch_error(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = custom_getenv("PWD", data->lst_env);
	printf("cd: error retrieving current directory:");
	printf("getcwd:cannot access parent directories:");
	printf(" No such file or directory\n");
	update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
	new_pwd = update_env(data, "OLDPWD", old_pwd);
	old_pwd = ft_strjoin(old_pwd, "/..");
	data->exit_stat = chdir(old_pwd);
	if (data->exit_stat)
		find_dir(data, old_pwd, old_pwd);
	return (data->exit_stat);
}

int	my_cd(t_data *data, t_cmd *lst_cmd)
{
	char	*cwd;
	char	**cmd;

	cmd = lst_cmd->cmd;
	cwd = getcwd(NULL, 0);
	if (cmd[1])
	{
		if (!cwd)
			data->exit_stat = catch_error(data);
		else
			return (my_chdir(data, cmd[1], cwd));
	}
	return (data->exit_stat);
}
